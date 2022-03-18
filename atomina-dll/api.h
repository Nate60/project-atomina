#pragma once

//Standard libaries can be ignored, other libaries are included
#pragma warning(disable: 4251 4275)

//MACRO definition for dll export and import
//requires that ATOMINADLL_EXPORTS is defined in preprocessor for only the dll project

#ifdef ATOMINADLL_EXPORTS
#define ATMA_API __declspec(dllexport)
#else
#define ATMA_API __declspec(dllimport)
#endif