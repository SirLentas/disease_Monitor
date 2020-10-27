make: dis_monitor.cpp hash_t.cpp list.cpp HeapList.cpp MaxHeap.cpp AVL.cpp
	g++ -o diseaseMonitor dis_monitor.cpp hash_t.cpp list.cpp HeapList.cpp MaxHeap.cpp AVL.cpp

.PHONY: clean

clean:
	rm -f diseaseMonitor
