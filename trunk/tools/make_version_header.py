# Copyright (c) 2011 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

from date_util import *
from file_util import *
from optparse import OptionParser
from svn_util import *
import sys

# cannot be loaded as a module
if __name__ != "__main__":
    sys.stderr.write('This file cannot be loaded as a module!')
    sys.exit()


# parse command-line options
disc = """
This utility creates the version header file.
"""

parser = OptionParser(description=disc)
parser.add_option('--header', dest='header', metavar='FILE',
                  help='output version header file [required]')
parser.add_option('--version', dest='version', metavar='FILE',
                  help='input Chrome version config file [required]')
parser.add_option('-q', '--quiet',
                  action='store_true', dest='quiet', default=False,
                  help='do not output detailed status information')
(options, args) = parser.parse_args()

# the header option is required
if options.header is None or options.version is None:
    parser.print_help(sys.stdout)
    sys.exit()

def write_svn_header(header, version):
    """ Creates the header file for the current revision and Chrome version information
       if the information has changed or if the file doesn't already exist. """

    if not path_exists(version):
      raise Exception('Version file '+version+' does not exist.')

    # Read and parse the version file (key=value pairs, one per line)
    chrome = {}
    lines = read_file(version).split("\n")
    for line in lines:
      parts = line.split('=', 1)
      if len(parts) == 2:
        chrome[parts[0]] = parts[1]

    if path_exists(header):
        oldcontents = read_file(header)
    else:
        oldcontents = ''

    year = get_year()

    newcontents = '// Copyright (c) '+year+' Marshall A. Greenblatt. All rights reserved.\n'+\
                  '//\n'+\
                  '// Redistribution and use in source and binary forms, with or without\n'+\
                  '// modification, are permitted provided that the following conditions are\n'+\
                  '// met:\n'+\
                  '//\n'+\
                  '//    * Redistributions of source code must retain the above copyright\n'+\
                  '// notice, this list of conditions and the following disclaimer.\n'+\
                  '//    * Redistributions in binary form must reproduce the above\n'+\
                  '// copyright notice, this list of conditions and the following disclaimer\n'+\
                  '// in the documentation and/or other materials provided with the\n'+\
                  '// distribution.\n'+\
                  '//    * Neither the name of Google Inc. nor the name Chromium Embedded\n'+\
                  '// Framework nor the names of its contributors may be used to endorse\n'+\
                  '// or promote products derived from this software without specific prior\n'+\
                  '// written permission.\n'+\
                  '//\n'+\
                  '// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS\n'+\
                  '// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT\n'+\
                  '// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR\n'+\
                  '// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT\n'+\
                  '// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,\n'+\
                  '// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT\n'+\
                  '// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,\n'+\
                  '// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY\n'+\
                  '// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT\n'+\
                  '// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE\n'+\
                  '// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n'+\
                  '//\n'+\
                  '// ---------------------------------------------------------------------------\n'+\
                  '//\n'+\
                  '// This file is generated by the make_version_header.py tool.\n'+\
                  '//\n\n'+\
                  '#ifndef _CEF_VERSION_H\n'+\
                  '#define _CEF_VERSION_H\n\n'+\
                  '#define CEF_REVISION ' + get_revision() + '\n'+\
                  '#define COPYRIGHT_YEAR ' + year + '\n\n'+\
                  '#define CHROME_VERSION_MAJOR ' + chrome['MAJOR'] + '\n'+\
                  '#define CHROME_VERSION_MINOR ' + chrome['MINOR'] + '\n'+\
                  '#define CHROME_VERSION_BUILD ' + chrome['BUILD'] + '\n'+\
                  '#define CHROME_VERSION_PATCH ' + chrome['PATCH'] + '\n\n'+\
                  '#define DO_MAKE_STRING(p) #p\n'+\
                  '#define MAKE_STRING(p) DO_MAKE_STRING(p)\n\n'+\
                  '#ifndef APSTUDIO_HIDDEN_SYMBOLS\n\n'\
                  '#ifdef __cplusplus\n'+\
                  'extern "C" {\n'+\
                  '#endif\n\n'+\
                  '#include "internal/cef_export.h"\n\n'+\
                  '///\n'+\
                  '// Returns the CEF build revision of the libcef library.\n'+\
                  '///\n'+\
                  'CEF_EXPORT int cef_build_revision();\n\n'+\
                  '#ifdef __cplusplus\n'+\
                  '}\n'+\
                  '#endif\n\n'+\
                  '#endif // APSTUDIO_HIDDEN_SYMBOLS\n\n'+\
                  '#endif // _CEF_VERSION_H\n'
    if newcontents != oldcontents:
        write_file(header, newcontents)
        return True

    return False

written = write_svn_header(options.header, options.version)
if not options.quiet:
  if written:
    sys.stdout.write('File '+options.header+' updated.\n')
  else:
    sys.stdout.write('File '+options.header+' is already up to date.\n')
