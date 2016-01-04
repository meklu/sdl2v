#include <dlfcn.h>
#include <SDL2/SDL.h>

void (*gv)(SDL_version *) = NULL;

void psv(void) {
	SDL_version v;
	if (!gv) {
		printf("SDL_GetVersion not found in sofile\n");
		return;
	}
	gv(&v);
	printf("SDL version %d.%d.%d\n", v.major, v.minor, v.patch);
}

int sv(const char *n) {
	void *h = NULL;
	h = dlopen(n, RTLD_LAZY | RTLD_GLOBAL);
	if (h == NULL) {
		fprintf(stderr, "Failed to open %s: %s\n", n, dlerror());
		return 0;
	}
	*(void **) (&gv) = dlsym(h, "SDL_GetVersion");
	if (gv == NULL) {
		fprintf(stderr, "%s\n", dlerror());
	}
	printf("%s: ", n);
	psv();
	gv = NULL;
	if (0 != dlclose(h)) {
		fprintf(stderr, "dlclose failed: %s\n", dlerror());
		return 0;
	}
	return 1;
}

int main(int argc, char **argv) {
	int ret = 0;
	const char *rn = "libSDL2.so";
	if (argc >= 2) {
		int i;
		char *n;
		for (i = 1; i < argc; i += 1) {
			n = argv[i];
			if (!sv(n)) { ret = 1; }
		}
	}
	if (!sv(rn)) { ret = 1; }
	return ret;
}
