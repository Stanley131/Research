import threading
import os
import queue

workloads = [1, 2, 3, 4, 5]

def worker():
	while True:
		try:
			j = q.get(block = 0)
		except queue.Empty:
			return

		print("Running: "+j)
		
		os.system(j)

q = queue.Queue()

for work in workloads:
    q.put(f'python3 dsalt_bo.py -a -b -w {work}')


#Create all worker threads
threads = []
number_worker_threads = 5

#Start threads to process jobs
for i in range(number_worker_threads):
	t = threading.Thread(target = worker)
	threads.append(t)
	t.start()

#Join all completed threads
for t in threads:
	t.join()
