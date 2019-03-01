#set(ex_h)

set(dijkstra_src 
	main.c
	fibHeap.c
	graph.c
	heapBin.c
	heapBinomialFra.c
)

set(dijkstra_h
	fibHeap.h
	graph.h
	heapBin.h
	heapBinomialFra.h
	heapType.h
)

add_executable(dijkstra_exe ${dijkstra_src} ${dijkstra_h} )
target_link_libraries(dijkstra_exe m)

