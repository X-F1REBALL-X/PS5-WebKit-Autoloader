#pragma once

/* 1 = already installed at this build's version; 0 = missing/outdated. */
int wkali_app_is_up_to_date(void);

/* Installs/updates the "WebKit Autoloader" homescreen app if needed. */
int wkali_install_app_if_needed(void);
