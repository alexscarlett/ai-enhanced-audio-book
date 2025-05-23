# JUCE plugin that loads an LSTM from a torchscript model and uses it to process audio

# Additional Instructions for M1 Mac

You'll need to build libtorch manually to work on M1 chips.

Go here: https://github.com/pytorch/pytorch/blob/main/docs/libtorch.rst

Run this in your terminal, but double check the link above to see if anything has changed...

```
git clone -b main --recurse-submodule https://github.com/pytorch/pytorch.git
mkdir pytorch-build
cd pytorch-build
cmake -DBUILD_SHARED_LIBS:BOOL=ON -DCMAKE_BUILD_TYPE:STRING=Release -DPYTHON_EXECUTABLE:PATH=`which python3` -DCMAKE_INSTALL_PREFIX:PATH=../pytorch-install ../pytorch
cmake --build . --target install
```

## Note for Windows users

When you load a plugin that is dynamically linked to libtorch in a plugin host, it will not be able to find the torch DLLs. The plugin load will therefore fail.

To solve this, you need to put the torch DLLs somewhere where Windows can find them.

You can find the torch DLLs in the lib sub folder of your torch folder. (the one you downloaded from the pytorch website). The files you want are these:

```
asmjit.dll
c10.dll
fbgemm.dll
libiomp5md.dll
libiompstubs5md.dll
torch.dll
torch_cpu.dll
torch_global_deps.dll
uv.dll
```

By default, Windows always looks in c:\Windows\System32 for DLLs. So you can just copy them there. This is the simplest, but not the cleanest solution. It is ok for dev work, but if you upgrade your torch version, you need to remember to copy the dlls over.

Other, more complex but cleaner options:

- Add the torch/lib folder to your PATH with an environment variable. https://www.wikihow.com/Change-the-PATH-Environment-Variable-on-Windows
- Call the SetDllDirectory function in your plugin constructor and add the location of the DLLs. https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-setdlldirectorya
