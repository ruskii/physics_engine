#include <iostream>
#include <functional>
#include <vector>
#include <condition_variable>
#include <queue>
#include <future>
//#include "vectors.h"
using namespace std;

class ThreadPool {
public:
	using Task = function<void()>;		// null return type, probally need changes
	explicit ThreadPool(size_t numThread) {start(numThread);}
	~ThreadPool() {stop();}

	template<class T>
	auto enqueue(T task)->future<decltype(task())> {
		auto wrapper = make_shared<packaged_task<decltype(task()) ()>>(move(task)); {
			unique_lock<mutex> lock(mEventMutex);
			mTasks.emplace([=] {
				(*wrapper)();
			});
		}

		mEventVar.notify_one();
		return wrapper->get_future();
	}

private:
	vector<thread> mThreads;

	condition_variable mEventVar;
	mutex mEventMutex;
	bool mStopping = false;

	queue<Task> mTasks;

	void start(size_t numThreads) {
		for (auto i = 0; i < numThreads; i++) {
			mThreads.emplace_back([=] {
				while (true) {
					Task task; {
						unique_lock<mutex> lock(mEventMutex);
						mEventVar.wait(lock, [=] { return mStopping || !mTasks.empty(); });

						if (mStopping && mTasks.empty()) break;

						task = move(mTasks.front());
						mTasks.pop();
					}
					task();
				}
			});
		}
	}

	void stop() noexcept {{
			unique_lock <mutex> lock{ mEventMutex };
			mStopping = true;
		}
		mEventVar.notify_all();

		for (auto &thread : mThreads)
			thread.join();
	}
};

int main() {{
		ThreadPool pool(16);
		//enqueue, replace cout with atcual task
		auto f1 = pool.enqueue([] {return 1;});
		auto f2 = pool.enqueue([] {return 2;});

		cout << f1.get() + f2.get() << endl;
	}

	system("read -p 'Press Enter to continue...' var");

	return 0;
}
