/*
 * ezcli - a minimal but flexible command line interface library for C.
 *
 * compile with 'make all' and run 'build/bin/ezdocs' for self-generated
 * documentation. or, go to https://ezcli.ozdinc.org/.
 *
 * author - Alperen Özdinç <alperen@ozdinc.org>
 * date - 14 Dec 2025
 * version - v1.2.7
 */

#pragma once

/*
  -------------------
  core public headers
  -------------------
*/

#include <ezcli/cli.h>
#include <ezcli/opt.h>

/*
  -----------------
  external controls
  -----------------
*/

#include <ezcli/external.h>
#include <ezcli/ezcliver.h>

/*
  --------------
  core functions
  --------------
*/

#include <ezcli/initcli.h>
#include <ezcli/runcli.h>

#ifndef CLI_EMBEDDED

#include <ezcli/freecli.h>

#endif // CLI_EMBEDDED

/*
  -----------------
  helpers/utilities
  -----------------
*/

#include <ezcli/gettok.h>
#include <ezcli/print.h>

#ifndef CLI_EMBEDDED

#include <ezcli/addopt.h>
#include <ezcli/allocopt.h>
#include <ezcli/askbinary.h>
#include <ezcli/autocomp.h>
#include <ezcli/center.h>
#include <ezcli/delopt.h>
#include <ezcli/window.h>

#endif // CLI_EMBEDDED
