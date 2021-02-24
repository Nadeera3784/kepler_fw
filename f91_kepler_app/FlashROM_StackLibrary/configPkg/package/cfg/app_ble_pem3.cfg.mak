# invoke SourceDir generated makefile for app_ble.pem3
app_ble.pem3: .libraries,app_ble.pem3
.libraries,app_ble.pem3: package/cfg/app_ble_pem3.xdl
	$(MAKE) -f C:\Users\pegor\Desktop\Projects\f91-sw\f91-fw\f91_kepler_app\TOOLS/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\pegor\Desktop\Projects\f91-sw\f91-fw\f91_kepler_app\TOOLS/src/makefile.libs clean

