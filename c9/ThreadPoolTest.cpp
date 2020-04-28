#include <chrono>
#include <mutex>
#include <condition_variable>

#include "ThreadPool.h"
#include "CppUTest/TestHarness.h"

using namespace std;
using namespace std::chrono;

TEST_GROUP(AThreadPool) {
   mutex m;
   ThreadPool pool;
};

TEST(AThreadPool, HasNoWorkOnCreation) {
   CHECK_FALSE(pool.hasWork());
}

TEST(AThreadPool, HasWorkAfterAdd) {
   pool.add(Work{1});
   CHECK_TRUE(pool.hasWork());
}

TEST(AThreadPool, AnswersWorkAddedOnPull) {
   pool.add(Work{1});
   auto work = pool.pullWork();

   LONGS_EQUAL(1, work.id());
}

TEST(AThreadPool, PullsElementsInFIFOOrder) {
   pool.add(Work{1});
   pool.add(Work{2});
   auto work = pool.pullWork();

   LONGS_EQUAL(1, work.id());
}

TEST(AThreadPool, HasNoWorkAfterLastElementRemoved) {
   pool.add(Work{});
   pool.pullWork();

   CHECK_FALSE(pool.hasWork());
}

TEST(AThreadPool, HasWorkAfterWorkRemovedButWorkRemains) {
   pool.add(Work{});
   pool.add(Work{});
   pool.pullWork();

   CHECK_TRUE(pool.hasWork());
}

TEST_GROUP(AThreadPool_AddRequest) {
   mutex m;
   ThreadPool pool;
   condition_variable wasExecuted;
   unsigned count {0};

   void setup() override {
      pool.start();
   }

   void incrementCountAndNotify() {
      std::unique_lock<std::mutex> lock(m);
      ++count;
      wasExecuted.notify_all();
   }

   void waitForCountAndFailOnTimeout(
         unsigned int expectedCount,
         const milliseconds& time=milliseconds(100)) {
      unique_lock<mutex> lock(m);
      CHECK_TRUE(wasExecuted.wait_for(lock, time,
            [&] { return expectedCount == count; }));
   }
};

TEST(AThreadPool_AddRequest, PullsWorkInAThread) {
   Work work{[&] { incrementCountAndNotify(); }};
   unsigned NumberOfWorkItems{1};

   pool.add(work);

   waitForCountAndFailOnTimeout(NumberOfWorkItems);
}

TEST(AThreadPool_AddRequest, ExecutesAllWork) {
   unsigned NumberOfWorkItems{3};
   Work work{ [&] { incrementCountAndNotify(); } };

   for (unsigned int i{0}; i < NumberOfWorkItems; i++)
      pool.add(work);
   waitForCountAndFailOnTimeout(NumberOfWorkItems);
}
