TARGET_SOURCES (${ProjectName}
	PRIVATE
	ResourceCollectionGenerator.hpp
	ResourceKind.hpp
	Parser.hpp
	ErrorStrings.hpp
	ResourceCollectionGenerator.cpp
	Parser.cpp
)

ADD_SUBDIRECTORY (_Language)