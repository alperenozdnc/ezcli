#pragma once

/*
 * gets and returns all absolute paths of all entries in `ezdocs/content` as
 * an array. its your responsibility to free the returned array.
 */
char **get_entries(char *path);
