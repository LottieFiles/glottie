buffer1 = Module._malloc(someArray.length * someArray.bytes)
Module.HEAP8.set(someArray, buffer)
buffer2 = Module._malloc(someOtherArray.length * someOtherArray.bytes)
Module.HEAP8.set(someOtherArray, buffer2)
Module.ccall("someCall", null, ["number", "number", "number", "number"],
		[buffer1, someArray.length, buffer2, someOtherArray.length])


