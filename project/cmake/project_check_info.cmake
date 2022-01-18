if(NOT DEFINED NCPROJECT_NAME)
	message(FATAL_ERROR "NCPROJECT_NAME variable is not set")
endif()

if(NOT DEFINED NCPROJECT_SOURCES)
	message(FATAL_ERROR "NCPROJECT_SOURCES variable is not set")
endif()

if(NOT DEFINED NCPROJECT_REVERSE_DNS)
	message(WARNING "NCPROJECT_REVERSE_DNS variable is not set")
	set(NCPROJECT_DESKTOP_FILE ${NCPROJECT_LOWER_NAME}.desktop)
	set(NCPROJECT_JAVA_URL ${NCPROJECT_LOWER_NAME})
else()
	string(FIND ${NCPROJECT_REVERSE_DNS} "-" DASH_FOUND_IN_DNS)
	if(DASH_FOUND_IN_DNS GREATER -1)
		message(WARNING "NCPROJECT_REVERSE_DNS variable cannot contain a dash character")
		string(REPLACE "-" "_" NCPROJECT_REVERSE_DNS ${NCPROJECT_REVERSE_DNS})
	endif()

	set(NCPROJECT_DESKTOP_FILE ${NCPROJECT_REVERSE_DNS}.desktop)
	string(REPLACE "." "/" NCPROJECT_JAVA_URL ${NCPROJECT_REVERSE_DNS})
endif()

if(NOT DEFINED NCPROJECT_XDGDESKTOP_CATEGORIES)
	set(NCPROJECT_XDGDESKTOP_CATEGORIES "Game")
endif()

if(NOT DEFINED NCPROJECT_MACOS_CATEGORY)
	set(NCPROJECT_MACOS_CATEGORY "public.app-category.games")
endif()

if(NCPROJECT_BUILD_ANDROID)
	if(NOT DEFINED NCPROJECT_ANDROID_ASSETS)
		message(WARNING "NCPROJECT_ANDROID_ASSETS variable is not set")
	elseif(NOT NCPROJECT_ANDROID_ASSETS)
		message(WARNING "NCPROJECT_ANDROID_ASSETS variable is set but it is an empty list")
	endif()
endif()

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/LICENSE")
	message(WARNING "Consider adding a \"LICENSE\" file in the root of the project")
endif()

string(TOLOWER ${NCPROJECT_NAME} NCPROJECT_LOWER_NAME)
string(TOUPPER ${NCPROJECT_NAME} NCPROJECT_UPPER_NAME)

if(NOT DEFINED NCPROJECT_EXE_NAME)
	set(NCPROJECT_EXE_NAME ${NCPROJECT_LOWER_NAME})
endif()

if(NOT DEFINED NCPROJECT_DESKTOP_FILE)
	set(NCPROJECT_DESKTOP_FILE ${NCPROJECT_LOWER_NAME}.desktop)
endif()

if(NOT DEFINED NCPROJECT_JAVA_URL)
	set(NCPROJECT_JAVA_URL ${NCPROJECT_LOWER_NAME})
endif()

message("${NCPROJECT_NAME} by ${NCPROJECT_VENDOR}")
message("${NCPROJECT_DESCRIPTION}")
message("${NCPROJECT_HOMEPAGE}")
message("${NCPROJECT_COPYRIGHT}\n")