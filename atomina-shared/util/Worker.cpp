#include "../pch.hpp"
#include "Worker.hpp"

namespace ATMA {

	using namespace std::chrono_literals;

	Worker::Worker()
	{

	}

	bool Worker::isDone() const
	{
		return m_future.wait_for(0ms) == std::future_status::ready && m_started;
	}

	bool Worker::hasStarted() const
	{
		return m_started;
	}

}