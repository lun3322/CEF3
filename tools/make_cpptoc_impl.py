# Copyright (c) 2010 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

from cef_parser import *

def make_cpptoc_impl_proto(name, func, parts):
    if isinstance(func, obj_function_virtual):
        proto = parts['retval']+' CEF_CALLBACK'
    else:
        proto = 'CEF_EXPORT '+parts['retval']
    
    proto += ' '+name+'('+string.join(parts['args'], ', ')+')'
    return wrap_code(proto)

def make_cpptoc_impl_existing(name, func, impl, defined_names):
    # retrieve the C API prototype parts
    parts = func.get_capi_parts(defined_names)
    
    changes = format_translation_changes(impl, parts)
    if len(changes) > 0:
        notify('Changed prototype for '+name)
    
    return make_cpptoc_impl_proto(name, func, parts)+'{'+ \
           changes+impl['body']+'\n}\n\n'
    return result

def make_cpptoc_impl_new(name, func, defined_names):
    notify('Added implementation for '+name)
    
    # retrieve the C API prototype parts
    parts = func.get_capi_parts(defined_names)
    result = make_cpptoc_impl_proto(name, func, parts)+'{'
    
    result += '\n  // BEGIN DELETE BEFORE MODIFYING'
    result += '\n  // AUTO-GENERATED CONTENT'
    
    result += '\n  #pragma message("Warning: "__FILE__": '+name+' is not implemented")'

    result += '\n  // END DELETE BEFORE MODIFYING'
    
    # NULL check all pointer arguments.
    if len(parts['args']) > 0:
        check = [];
        for arg in parts['args']:
            if arg.find('*') >= 0:
                argname = string.split(arg)[-1];
                result += '\n  DCHECK('+argname+');'
                check.append('!'+argname);
        result += '\n  if ('+string.join(check,' || ')+')'
        result += '\n    return;'
    
    result += '\n}\n\n'
    return result

def make_cpptoc_impl(header, clsname, impl):
    # structure names that have already been defined
    defined_names = header.get_defined_structs()
    
    # retrieve the class and populate the defined names
    cls = header.get_class(clsname, defined_names)
    if cls is None:
        raise Exception('Class does not exist: '+clsname)
    
    defname = string.upper(clsname[3:])
    capiname = cls.get_capi_name()
    prefixname = get_capi_name(clsname[3:], False)
    
    # retrieve the existing virtual function implementations
    existing = get_function_impls(impl, 'CEF_CALLBACK')
    
    # generate virtual functions
    virtualimpl = ''
    funcs = cls.get_virtual_funcs()
    for func in funcs:
        name = prefixname+'_'+func.get_capi_name()
        value = get_next_function_impl(existing, name)
        if not value is None \
            and value['body'].find('// AUTO-GEN') < 0:
            # an implementation exists that was not auto-generated
            virtualimpl += make_cpptoc_impl_existing(name, func, value,
                defined_names)
        else:
            virtualimpl += make_cpptoc_impl_new(name, func, defined_names)
    
    if len(virtualimpl) > 0:
        virtualimpl = '\n// MEMBER FUNCTIONS - Body may be edited by hand.\n\n'+virtualimpl
      
    # the current class is already defined for static functions 
    defined_names.append(cls.get_capi_name())
            
    # retrieve the existing static function implementations
    existing = get_function_impls(impl, 'CEF_EXPORT')
    
    # generate static functions
    staticimpl = ''
    funcs = cls.get_static_funcs()
    for func in funcs:
        name = func.get_capi_name()
        value = get_next_function_impl(existing, name)
        if not value is None \
            and value['body'].find('// AUTO-GENERATED CONTENT') < 0:
            # an implementation exists that was not auto-generated
            staticimpl += make_cpptoc_impl_existing(name, func, value,
                defined_names)
        else:
            staticimpl += make_cpptoc_impl_new(name, func, defined_names)
    
    if len(staticimpl) > 0:
        staticimpl = '\n// GLOBAL FUNCTIONS - Body may be edited by hand.\n\n'+staticimpl
      
    resultingimpl = staticimpl + virtualimpl
    
    # determine what includes are required by identifying what translation
    # classes are being used
    includes = format_translation_includes(resultingimpl)
    
    # build the final output
    result = \
"""// Copyright (c) 2010 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// A portion of this file was generated by the CEF translator tool.  When
// making changes by hand only do so within the body of existing function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//

"""
    
    result += includes+'\n'+resultingimpl+'\n'
    
    const =  '// CONSTRUCTOR - Do not edit by hand.\n\n'+ \
             clsname+'CppToC::'+clsname+'CppToC('+clsname+'* cls)\n'+ \
             '    : CefCppToC<'+clsname+'CppToC, '+clsname+', '+capiname+'>(cls)\n'+ \
             '{\n';
                
    funcs = cls.get_virtual_funcs()
    for func in funcs:
        name = func.get_capi_name()
        const += '  struct_.struct_.'+name+' = '+prefixname+'_'+name+';\n'
                
    const += '}\n\n'+ \
             '#ifdef _DEBUG\n'+ \
             'template<> long CefCppToC<'+clsname+'CppToC, '+clsname+', '+capiname+'>::DebugObjCt = 0;\n'+ \
             '#endif\n'
    result += wrap_code(const)

    return result


def write_cpptoc_impl(header, clsname, dir, backup):
    file = dir+os.sep+get_capi_name(clsname[3:], False)+'_cpptoc.cc'
    
    if file_exists(file):
        oldcontents = read_file(file)
    else:
        oldcontents = ''
    
    newcontents = make_cpptoc_impl(header, clsname, oldcontents)
    if newcontents != oldcontents:
        if backup and oldcontents != '':
            backup_file(file)
        write_file(file, newcontents)
        return True
    
    return False


# test the module
if __name__ == "__main__":
    import sys
    
    # verify that the correct number of command-line arguments are provided
    if len(sys.argv) < 4:
        sys.stderr.write('Usage: '+sys.argv[0]+' <infile> <classname> <existing_impl>')
        sys.exit()
        
    # create the header object
    header = obj_header(sys.argv[1])
    
    # read the existing implementation file into memory
    try:
        f = open(sys.argv[3], 'r')
        data = f.read()
    except IOError, (errno, strerror):
        raise Exception('Failed to read file '+sys.argv[3]+': '+strerror)
    else:
        f.close()
    
    # dump the result to stdout
    sys.stdout.write(make_cpptoc_impl(header, sys.argv[2], data))
