project(chapter7)
cmake_minimum_required(VERSION 2.6)

include_directories(include)
add_definitions(-std=c++11)

set(sources
	Book.cpp
	Branch.cpp
	BranchAccess.cpp
	BranchService.cpp
	Catalog.cpp
	ClassificationService.cpp
	Endpoint.cpp
	EndpointValidator.cpp
	Holding.cpp
	HoldingService.cpp
	InventoryReport.cpp
	MailDestination.cpp
	MailMessage.cpp
	Patron.cpp
	PatronAccess.cpp
	PatronService.cpp
	RomanConverter.cpp
	Scanner.cpp
	ScannerState.cpp
	ScannerStateCheckin.cpp
	ScannerStateCheckout.cpp
	ScannerStateInventory.cpp
	ScannerStateWaiting.cpp
	StreamLineReader.cpp
	TimestampSource.cpp
	Transport.cpp
	)
add_library(library ${sources})
target_link_libraries(library pthread)
target_link_libraries(library rt)
