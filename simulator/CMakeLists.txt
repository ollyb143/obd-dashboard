add_executable(obd_simulator
        obd_simulator.cpp
)

# Optional if it needs shared headers
target_include_directories(obd_simulator PRIVATE ../include)
