#include "lib.hpp"
#include "nn/fs.hpp"
/* Define hook StubCopyright. Trampoline indicates the original function should be kept. */
/* HOOK_DEFINE_REPLACE can be used if the original function does not need to be kept. */
// HOOK_DEFINE_TRAMPOLINE(StubCopyright) {

//     /* Define the callback for when the function is called. Don't forget to make it static and name it Callback. */
//     static void Callback(bool enabled) {

//         /* Call the original function, with the argument always being false. */
//         Orig(false);
//     }

// };

void mountRomDetour(char const* name, void* arg2, unsigned long arg3) {
    // nn::fs::MountSdCardForDebug("sd");
    // nn::fs::CreateFile("sd:/detour.txt", 0);
    // nn::fs::FileHandle handle = nn::fs::FileHandle { 0 };
    // nn::fs::OpenFile(&handle, "sd:/detour.txt", nn::fs::OpenMode_Append | nn::fs::OpenMode_Write);
    // nn::fs::WriteFile(handle, 0, "detour!", 7, nn::fs::WriteOption::CreateOption(nn::fs::WriteOptionFlag_Flush));
    // nn::fs::CloseFile(handle);
}

/* Declare function to dynamic link with. */

extern "C" void exl_main(void* x0, void* x1) {
    /* Setup hooking enviroment. */
    envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::hook::Initialize();

    /* Install the hook at the provided function pointer. Function type is checked against the callback function. */
    // StubCopyright::InstallAtFuncPtr(nn::oe::SetCopyrightVisibility);
    exl::hook::nx64::install_hook(reinterpret_cast<const void*>(nn::fs::MountRom), reinterpret_cast<const void*>(mountRomDetour), exl::hook::nx64::HookHandlerType::Detour);

    /* Alternative install funcs: */
    /* InstallAtPtr takes an absolute address as a uintptr_t. */
    /* InstallAtOffset takes an offset into the main module. */

    /*
    For sysmodules/applets, you have to call the entrypoint when ready
    exl::hook::CallTargetEntrypoint(x0, x1);
    */
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}