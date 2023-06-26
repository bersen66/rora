add_custom_target(
	copy_resources ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${PROJECT_SOURCE_DIR}/resources
	${PROJECT_BINARY_DIR}/rora/resources
	COMMENT "Copying resources...."
)