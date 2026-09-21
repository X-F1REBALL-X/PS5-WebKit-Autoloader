#pragma once

/**
 * Launch the PS5 web browser with a specific URL.
 * @param uri The URL to open.
 * @return 0 on success, -1 on failure.
 */
int ps5_launch_browser(const char *uri);

/**
 * Return to the PS5 home screen (closes the WebKit browser cleanly).
 * @return 0 on success, negative on failure.
 */
int ps5_return_to_home(void);
