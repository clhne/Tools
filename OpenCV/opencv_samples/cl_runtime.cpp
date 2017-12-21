#include "precomp.hpp"

#if defined(HAVE_OPENCL) && !defined(HAVE_OPENCL_STATIC)

#include "opencv2/ocl/cl_runtime/cl_runtime.hpp"

#if defined(__APPLE__)
    #include <dlfcn.h>

    static void* AppleCLGetProcAddress(const char* name)
    {
        static void * image = NULL;
        if (!image)
        {
            image = dlopen("/System/Library/Frameworks/OpenCL.framework/Versions/Current/OpenCL", RTLD_LAZY | RTLD_GLOBAL);
            if (!image)
                return NULL;
        }

        return dlsym(image, name);
    }
    #define CV_CL_GET_PROC_ADDRESS(name) AppleCLGetProcAddress(name)
#endif // __APPLE__

#if defined(_WIN32)
    static void* WinGetProcAddress(const char* name)
    {
        static HMODULE opencl_module = NULL;
        if (!opencl_module)
        {
            opencl_module = GetModuleHandleA("OpenCL.dll");
            if (!opencl_module)
            {
                const char* libName = "OpenCL.dll";
                const char* envOpenCLBinary = getenv("OPENCV_OPENCL_BINARY");
                if (envOpenCLBinary)
                    libName = envOpenCLBinary;
                opencl_module = LoadLibraryA(libName);
                if (!opencl_module)
                    return NULL;
            }
        }
        return (void*)GetProcAddress(opencl_module, name);
    }
    #define CV_CL_GET_PROC_ADDRESS(name) WinGetProcAddress(name)
#endif // _WIN32

#if defined(__linux__)&&!defined(__ANDROID__)
    #include <dlfcn.h>
    #include <stdio.h>

    static void* GetProcAddress (const char* name)
    {
        static void* h = NULL;
        if (!h)
        {
            const char* name = "libOpenCL.so";
            const char* envOpenCLBinary = getenv("OPENCV_OPENCL_BINARY");
            if (envOpenCLBinary)
                name = envOpenCLBinary;
            h = dlopen(name, RTLD_LAZY | RTLD_GLOBAL);
            if (!h)
                return NULL;
        }

        return dlsym(h, name);
    }
    #define CV_CL_GET_PROC_ADDRESS(name) GetProcAddress(name)
#endif

#if defined(__ANDROID__)
    #include <dlfcn.h>
    #include <sys/stat.h>
#if defined(__ARM_ARCH_8A__) || defined(_X64_)
    static const char *default_so_paths[] = {
                                            "/system/lib64/libOpenCL.so",
                                            "/system/lib/egl/libGLES_mali.so",
                                            "/system/vendor/lib64/libOpenCL.so",
                                            "/system/vendor/lib64/egl/libGLES_mali.so"
                                          };
#else
    static const char *default_so_paths[] = {
                                            "/system/lib/libOpenCL.so",
                                            "/system/lib/egl/libGLES_mali.so",
                                            "/system/vendor/lib/libOpenCL.so",
                                            "/system/vendor/lib/egl/libGLES_mali.so"
                                          };
#endif
    static int access_file(const char *filename)
    {
        struct stat buffer;
        return (stat(filename, &buffer) == 0);
    }

    static void* GetProcAddress (const char* name)
    {
        static void* h = NULL;
        unsigned int i;
        if (!h)
        {
            const char* name;
            for(i=0; i<(sizeof(default_so_paths)/sizeof(char*)); i++)
            {
                if(access_file(default_so_paths[i])) {
                    name = (char *)default_so_paths[i];
                    h = dlopen(name, RTLD_LAZY);
                    if (h) break;
                }
            }
            if (!h)
                return NULL;
        }

        return dlsym(h, name);
    }
    #define CV_CL_GET_PROC_ADDRESS(name) GetProcAddress(name)
#endif  //android

#ifndef CV_CL_GET_PROC_ADDRESS
#define CV_CL_GET_PROC_ADDRESS(name) NULL
#endif

static void* opencl_check_fn(int ID)
{
    extern const char* opencl_fn_names[];
    void* func = CV_CL_GET_PROC_ADDRESS(opencl_fn_names[ID]);
    if (!func)
    {
        std::ostringstream msg;
        msg << "OpenCL function is not available: [" << opencl_fn_names[ID] << "]";
        CV_Error(CV_StsBadFunc, msg.str());
    }
    extern void* opencl_fn_ptrs[];
    *(void**)(opencl_fn_ptrs[ID]) = func;
    return func;
}

#include "cl_runtime_opencl_impl.hpp"

#endif
