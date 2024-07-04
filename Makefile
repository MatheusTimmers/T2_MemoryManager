compile:
	g++ .\src\Main.cpp .\src\MemoryManager\PartitionMemoryManager\PartitionMemoryManager.cpp .\src\Enums\Enums.cpp .\src\MemoryManager\Segment\Segment.cpp .\src\FileReader\FileReader.cpp -o run.exe
	.\run.exe
