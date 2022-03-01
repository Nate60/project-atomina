#pragma once
#include "pch.h"
#include "api.h"

namespace ATMA {

	class ATMA_API Worker
	{
	public:
		Worker();

		bool isDone() const;
		bool hasStarted() const;

	protected:
		virtual void work() = 0;
		std::future<void> m_future = std::async(&Worker::work, this);
		std::mutex m_mtx;
		std::atomic<bool> m_started;
	};

}

