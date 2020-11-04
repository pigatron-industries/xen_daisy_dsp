Import("env")

print()
print("================= Pigatron Industries ==================")
print()
print(env.Dump())
print()

if 'BUILD_FLAGS' in env:

    env['BUILD_FLAGS'].append('-w -D PIO_FRAMEWORK_ARDUINO_ENABLE_CDC -D USBCON -D ')
    env['BUILD_FLAGS'].append('-DHAL_SDRAM_MODULE_ENABLED=1 ')
    env['BUILD_FLAGS'].append('-DHAL_MDMA_MODULE_ENABLED=1 ')
    env['BUILD_FLAGS'].append('-DHAL_DMA_MODULE_ENABLED=1 ')
    env['BUILD_FLAGS'].append('-DINSTRUCTION_CACHE_ENABLE=1 ')

    includes = ""
    registers = ""

    for buildFlag in env['BUILD_FLAGS']:
        print(buildFlag)
        if buildFlag.startswith('-DAPP'):
            print("Adding App: " + buildFlag)
            appFlags = buildFlag.split("/")
            includes = includes + "#include \"apps/" + appFlags[1] + "/" + appFlags[2].lower() + "/"+ appFlags[2] + "Controller.h\"\n"
            includes = includes + appFlags[2] + "Controller " + appFlags[2] + "_;\n"
            registers = registers + "    MainController::instance.registerController(&" + appFlags[2] + "_);\n"

    f = open("src/apps.h", "w")
    f.write("/* autogenerated */\n")
    f.write("#ifndef apps_h\n")
    f.write("#define apps_h\n")
    f.write(includes)
    f.write("void registerApps() {\n")
    f.write(registers)
    f.write("}\n")
    f.write("#endif\n")
    f.close()

print()
print("================= Pigatron Industries ==================")
print()