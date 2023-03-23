import random
import threading
import time

# initialize global variable and lock
count = 0
lock = threading.Lock()


# thread worker, sleep for random seconds between 1 - 5
def thread_func(id):
    global count
    lock.acquire()
    print(f"Thread {id}: count = {count}")
    time.sleep(random.randint(1, 5))
    count += 1
    print(f"Thread {id}: count++")
    lock.release()


if __name__ == '__main__':
    thread_num = 4
    threads = []
    thread_ids = []

    for i in range(thread_num):
        thread_ids.append(i)

    # create threads and run
    for i in range(thread_num):
        t = threading.Thread(target=thread_func, args=(thread_ids[i],))
        threads.append(t)
        t.start()

    # wait for threads to complete
    for t in threads:
        t.join()

    print("Threads completed")
