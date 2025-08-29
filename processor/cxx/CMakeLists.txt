set(LLVM_LINK_COMPONENTS support)

add_executable(preprocessor
    preprocessor.cc
)

add_executable(cgprocessor
cgprocessor.cc
)

target_link_libraries(preprocessor
    PRIVATE
    clangTooling
    clangBasic
    clangASTMatchers
)

target_link_libraries(cgprocessor
    PRIVATE
    clangTooling
    clangBasic
    clangASTMatchers
)