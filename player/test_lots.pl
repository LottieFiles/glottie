for ($i = 0; $i < 50; $i++) {
	if (fork()) {
		$returned = `cat test.json | lottieplayer 1 1 1 1`;
	}
}
