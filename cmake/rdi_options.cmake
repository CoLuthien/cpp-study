

option(RENGINE_USE_VULKAN "Use Vulkan" ON)
option(RENGINE_VULKAN_USE_VALIDATION_LAYER "Use Vulkan Validation Layer" ON)

set(RDI_COMPILE_DEFINITIONS 
)

set(RDI_VULKAN_COMPILE_DEFINITIONS
    VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
)


if (RENGINE_VULKAN_USE_VALIDATION_LAYER)
    set(RDI_VULKAN_COMPILE_DEFINITIONS 
        ${RDI_VULKAN_COMPILE_DEFINITIONS}
        USE_VALIDATION_LAYER
    )
endif()

if (RENGINE_USE_VULKAN)
    set(RDI_COMPILE_DEFINITIONS
        ${RDI_COMPILE_DEFINITIONS}
        ${RDI_VULKAN_COMPILE_DEFINITIONS}
    )
endif()