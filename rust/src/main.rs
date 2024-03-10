extern crate libloading;
extern crate winapi;

use std::ffi::CString;

fn load_dll_from_file(dll_path: &str) -> Result<libloading::Library, String> {
    // Load the DLL
    let lib = libloading::Library::new(dll_path).map_err(|e| format!("Failed to load DLL: {}", e))?;
    Ok(lib)
}

fn main() {
    let dll_path = "c:\\windows\\system32\\kernel32.dll";
    let kernellib = match load_dll_from_file(dll_path) {
        Ok(kernellib) => kernellib,
        Err(err) => {
            eprintln!("{}", err);
            return;
        }
    };
    //println!("Kernel32 DLL loaded successfully!");

    let dll_path = "c:\\path\\to\\python311.dll";
    // let pythonlib = unsafe { LoadLibraryA(dll_path.as_ptr() as LPCSTR) };
    let pythonlib = match load_dll_from_file(dll_path) {
        Ok(pythonlib) => pythonlib,
        Err(err) => {
            eprintln!("{}", err);
            return;
        }
    };

    unsafe {
        let func_name = CString::new("LoadLibraryA").unwrap();
        let loadlib = kernellib.get::<libloading::Symbol<unsafe extern "stdcall" fn(lpFileName: &[u8]) -> i32 >>(func_name.as_bytes()).unwrap_or_else(|err| {
            eprintln!("Failed to get function address: {:?}", err);
            std::process::exit(1);
        });

        let func_name = CString::new("Py_InitializeEx").unwrap();
        let pyinit = pythonlib.get::<libloading::Symbol<unsafe extern "stdcall" fn(flags: i32) -> ()>>(func_name.as_bytes()).unwrap_or_else(|err| {
            eprintln!("Failed to get function address: {:?}", err);
            std::process::exit(1);
        });
        let func_name = CString::new("PyRun_SimpleString").unwrap();
        let pyrun = pythonlib.get::<libloading::Symbol<unsafe extern "stdcall" fn(script: *const u8) -> i32 >>(func_name.as_bytes()).unwrap_or_else(|err| {
            eprintln!("Failed to get function address: {:?}", err);
            std::process::exit(1);
        });
        let func_name = CString::new("Py_Finalize").unwrap();
        let pyfinish = pythonlib.get::<libloading::Symbol<unsafe extern "stdcall" fn() -> ()>>(func_name.as_bytes()).unwrap_or_else(|err| {
            eprintln!("Failed to get function address: {:?}", err);
            std::process::exit(1);
        });

        loadlib(b"c:\\path\\to\\_ctypes.pyd");
        loadlib(b"c:\\path\\to\\libffi-7.pyd");

        pyinit(0);

        let script = "
        paste your cradly.py here as a multiline string and terminate with a \0
        ";
        let _result = pyrun(script.as_ptr());

        pyfinish();
    }
}
