; Petitions
; ---------

; Core version
; -------------
core = 7.x

; API version
; ------------
api = 2

; Defaults
; ---------
defaults[projects][subdir] = contrib

; Contrib projects
; -----------------
projects[advanced_help][version] = 1.0

projects[captcha][version] = 1.0

projects[colorbox][version] = 2.4

projects[conditional_styles][version] = 2.1

projects[context][version] = 3.1

projects[ctools][version] = 1.3

projects[date][version] = 2.6

projects[diff][version] = 3.2

projects[email_confirm][version] = 1.1

projects[entity][version] = 1.2

projects[entitycache][version] = 1.2

projects[entityreference][version] = 1.1

projects[eva][version] = 1.2

projects[features][version] = 1.0

projects[feeds][version] = 2.0-alpha8

projects[forward][version] = 1.4

projects[globalredirect][version] = 1.5

projects[google_analytics][version] = 1.2

projects[govdelivery][version] = 1.0-alpha1

projects[imce][version] = 1.7

projects[job_scheduler][version] = 2.0-alpha3

projects[maintenance200][version] = 1.0

projects[memcache][version] = 1.0

projects[metatag][version] = 1.0-beta7

projects[migrate_extras][version] = 2.5

projects[mongodb][version] = 1.0-rc2

projects[openidadmin][version] = 1.0

projects[pathauto][version] = 1.2

projects[profile2][version] = 1.3

projects[recaptcha][version] = 1.10

; Latest stable release of Rules module is 2.4 however there is a fatal error
; when attempting to upgrade: https://drupal.org/node/2090511
; The latest security release is 2.3 so we can update to that for now:
; https://drupal.org/node/1954592
projects[rules][version] = 2.3

projects[services_documentation][version] = 1.3

projects[shunt][version] = 1.3

projects[simplehtmldom][version] = 1.12

projects[strongarm][version] = 2.0

projects[token][version] = 1.5

projects[views][version] = 3.7

projects[views_infinite_scroll][version] = 1.1

projects[views_bulk_operations][version] = 3.1

projects[wysiwyg][version] = 2.2

; Patched contrib
;-----------------

; libraries-undefined-index-foo.patch
;   - Fixes PHP warning on cache clear.
;   - @see https://drupal.org/node/1938638
projects[libraries][version] = 2.1
projects[libraries][patch][] = https://drupal.org/files/libraries-undefined-index-foo.patch

; migrate-mongodb-source-1890610-7.patch
;   - Adds a mongodb source.
;   - @see https://drupal.org/node/1890610
projects[migrate][download][type] = git
projects[migrate][download][url] = http://git.drupal.org/project/migrate.git
projects[migrate][download][revision] = 21895c810fc4beafe61389033445cb3b97586f05
projects[migrate][patch][] = https://drupal.org/files/migrate-mongodb-source-1890610-7.patch

; 1747878-2-remove-lower.patch
;   - Performance improvement, get rid of mysql LOWER(), it creates a temp table for the whole table
;   - @see http://drupal.org/node/1747878
;
; password_token-1165126-6.patch
;   - Make password available as a token
;   - @see http://drupal.org/node/1165126#comment-5492890
;

; textcaptcha-cron_default-2144807-1.patch
;   - Sets the textcaptcha_cron variable to 0 by default.
projects[textcaptcha][version] = 1.3
projects[textcaptcha][patch][] = https://drupal.org/files/issues/textcaptcha-cron_default-2144807-1.patch

; zen-include_error-2144803-1.patch
;   - Fixes Simpletest error.
projects[zen][type] = theme
projects[zen][subdir] = ""
projects[zen][version] = 5.4
projects[zen][patch][] = https://drupal.org/files/issues/zen-include_error-2144803-1.patch

;------------------------------------
projects[logintoboggan][version] = 1.3
projects[logintoboggan][patch][] = http://drupal.org/files/1747878-2-remove-lower.patch
projects[logintoboggan][patch][] = http://drupal.org/files/password_token-1165126-6.patch

; check_type.patch
;  - Data types were not checked before getting 'status' key from them
;  - @see http://drupal.org/node/1572368
;
; check_checks.patch
;   - Improved error handling.
;     Before we run checks, lets see if the checks for this module are enabled otherwise, break out of the loop.
;   - @see http://drupal.org/node/1747870
;
;------------------------------------
projects[nagios][version] = 1.1
projects[nagios][patch][] = http://drupal.org/files/check_type.patch
projects[nagios][patch][] = http://drupal.org/files/check_checks.patch

; services-1937312-format-arguments-errors-reroll-8.patch
;  - Fixes WSOD when missing required arguments.
;  - @see https://drupal.org/node/1937312
projects[services][version] = 3.5
projects[services][patch][] = http://drupal.org/files/services-1937312-format-arguments-errors-reroll-8.patch

; Contrib themes
; -----------------
projects[tao][type] = theme
projects[tao][subdir] = ""
projects[tao][version] = 3.0-beta4

projects[rubik][type] = theme
projects[rubik][subdir] = ""
projects[rubik][version] = 4.0-beta9

; 5ba70aaf95bf646211cc1d3086074885914c37cf
;  - Fixes coding standards violations, including a PHP short tag that causes
;    problems for simpletest.
projects[fortyfour][type] = theme
projects[fortyfour][subdir] = ""
projects[fortyfour][version] = 1.0-alpha7
projects[fortyfour][patch][] = http://drupalcode.org/project/fortyfour.git/patch/5ba70aaf95bf646211cc1d3086074885914c37cf

; External libraries
; -----------------

libraries[colorbox][download][type] = "file"
libraries[colorbox][download][url] = "https://github.com/jackmoore/colorbox/archive/1.4.27.zip"
libraries[faker][download][type] = "get"
libraries[faker][download][url] = "https://github.com/fzaninotto/Faker/archive/v1.3.0.tar.gz"

; jquery plugin required for views_infinite_scroll to work
; Calling this library js is a trick to get the file to the right spot, it should be fixed
libraries[js][download][type] = "file"
libraries[js][download][url] = "http://jquery-autopager.googlecode.com/files/jquery.autopager-1.0.0.js"
libraries[js][destination] = "modules/contrib/views_infinite_scroll"