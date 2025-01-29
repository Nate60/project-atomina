#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "Resource.hpp"
#include "ResourceLoader.hpp"
#include "loaders/DummyResourceLoader.hpp"
#include "loaders/AudioWaveLoader.hpp"
#include "loaders/GLShaderLoader.hpp"
#include "loaders/GLTextureLoader.hpp"
#include "util/AtominaException.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    using ResourceID = unsigned int;
    using ResourceTypeID = unsigned int;

    using ResourceContainer =
        std::unordered_map<ResourceID, std::tuple<ResourceTypeID, std::string, std::optional<std::string>>>;
    using LoadedResourceContainer = std::unordered_map<ResourceID, std::shared_ptr<LoadedResource>>;

    class ResourceManager
    {
    public:
        ResourceManager();

        virtual ~ResourceManager();

        /**
         * registers a resource to the context and assigns it an id
         * @param l_name name of the resource
         * @param l_resourceType type id of the resource
         * @param l_filename full qualified path to the resource
         * @returns id of the registered resource
         */
        [[nodiscard]] unsigned int registerResource(
            const std::string &l_name,
            const unsigned int &l_resourceType,
            const std::optional<std::string> &l_filename = std::nullopt
        );

        /**
         * checks if the resource has been registered
         * @param l_resourceID id of the resource to check for
         * @returns if the resource has been found
         */
        [[nodiscard]] bool hasResource(const unsigned int &l_resourceID);

        /**
         * loads the resource into memory from its source and gives a pointer
         * to the loaded resource
         * @tparam type class of the resource
         * @param l_resourceID id of the registered resource
         * @returns pointer to the resource loaded in memory
         * @throws ValueNotFound Exception if the id is not registered in the context
         */
        template<class T>
        [[nodiscard]] std::shared_ptr<T> loadResource(const unsigned int &l_resourceID)
        {
            auto itr = m_resources.find(l_resourceID);
            if(itr == m_resources.end())
            {
                throw ValueNotFoundException(
                    "resource ID: " + std::to_string(l_resourceID) + " has not been registered with ATMA Context"
                );
            }
            else
            {

                if(auto loadeditr = m_loadedResources.find(l_resourceID); loadeditr == m_loadedResources.end())
                {
                    ResourceLoader<T> loader{};
                    auto &name = std::get<1>(itr->second);
                    if(auto &filename = std::get<2>(itr->second); filename.has_value())
                    {
                        m_loadedResources[l_resourceID] = loader.load(name, Path{filename.value()});
                    }
                    else
                    {
                        m_loadedResources[l_resourceID] = loader.load(name);
                    }
                    return std::static_pointer_cast<T>(m_loadedResources[l_resourceID]);
                }
                else
                {
                    return std::static_pointer_cast<T>(loadeditr->second);
                }
            }
        }

        /**
         * checks if the resource id has been loaded into memory
         * @param l_resourceID id of the resource
         * @returns if the loaded resource is found
         */
        [[nodiscard]] bool hasLoadedResource(const unsigned int &l_resourceID);

        /**
         * removes the loaded resource from the context so it can no new pointers can be grabbed
         * from the context
         * @param l_resourceID id of the loaded resource
         * @throws ValueNotFound Exception if the id has no loaded resource
         */
        void unloadResource(const unsigned int &l_resourceID);

        /**
         * removes the registered resource from the context so it cannot longer be loaded
         * @param l_resourceID id of the registered resource
         * @throws ValueNotFound Exception if the id has no registered resource
         */
        void removeResource(const unsigned int &l_resourceID);

        /**
         * removes and unloads all resources from the context and resets the next id
         * back to 0
         */
        void purge();
    protected:
        ResourceContainer m_resources{};
        LoadedResourceContainer m_loadedResources{};
        ResourceID m_lastResourceId{0u};
    };
}
