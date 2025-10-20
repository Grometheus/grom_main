#include <cstdlib>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <drm/drm_mode.h>

 #include <dlfcn.h>



#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>


#include "minuitwrp/minui.h"
#include "graphics.h"

#include "build/stubs.h"


#include <string>



int redirect_std(const char *filename){
    // Open the file for writing (create if not exists, truncate if it does)
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }

    // Redirect stdout (file descriptor 1)
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2 stdout");
        close(fd);
        return EXIT_FAILURE;
    }

    // Redirect stderr (file descriptor 2)
    if (dup2(fd, STDERR_FILENO) < 0) {
        perror("dup2 stderr");
        close(fd);
        return EXIT_FAILURE;
    }

    // fd is no longer needed after dup2()
    close(fd);

    return EXIT_SUCCESS;
}



#define ANDROID_RB_RESTART  0xDEAD0001
#define ANDROID_RB_POWEROFF 0xDEAD0002
extern "C" int android_reboot(int cmd, int flags, const char *arg);





static void die(const char *msg) {
    perror(msg);
    exit(1);
}





int vibrate(int timeout_ms);


int main() {
  redirect_std("/tmp/out.log");

  if (init_miniui()) return -1;

  // Initialize the graphics system
  if (gr_init() < 0) {
      return -1;
  }

  // Get display dimensions
  int w = gr_fb_width();
  int h = gr_fb_height();

  // Clear the screen (black background)

  // Set text color (white)
  gr_color(255, 0, 255, 255);

  gr_fill(0, 0, w, h);


  gr_flip();


  vibrate(5000);

  // Keep it visible for a few seconds
  sleep(60);

  // Shutdown
  gr_exit();






   return 0;
}
