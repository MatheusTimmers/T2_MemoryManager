compile:
	g++ .\src\Main.cpp .\src\MemoryManager\Buddy\Buddy.cpp .\src\MemoryManager\PartitionMemoryManager\PartitionMemoryManager.cpp .\src\Enums\Enums.cpp .\src\MemoryManager\Segment\Segment.cpp .\src\FileReader\FileReader.cpp .\src\MemoryManager\BuddyMemoryManager\BuddyMemoryManager.cpp -o run.exe
	.\run.exe
