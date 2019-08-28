#!/usr/bin/env python2
# -*- coding:utf-8 -*-

def banner():
    print("=============================================")
    print("   Simple calculator implemented by python   ")
    print("=============================================")
    return

def getexp():
    return input(">>> ")

def _hook_import_(name, *args, **kwargs):
    print("be here 2-------------------------------------------------------------------", name)
    module_blacklist = ['os', 'sys', 'time', 'bdb', 'bsddb', 'cgi',
                        'CGIHTTPServer', 'cgitb', 'compileall', 'ctypes', 'dircache',
                        'doctest', 'dumbdbm', 'filecmp', 'fileinput', 'ftplib', 'gzip',
                        'getopt', 'getpass', 'gettext', 'httplib', 'importlib', 'imputil',
                        'linecache', 'macpath', 'mailbox', 'mailcap', 'mhlib', 'mimetools',
                        'mimetypes', 'modulefinder', 'multiprocessing', 'netrc', 'new',
                        'optparse', 'pdb', 'pipes', 'pkgutil', 'platform', 'popen2', 'poplib',
                        'posix', 'posixfile', 'profile', 'pstats', 'pty', 'py_compile',
                        'pyclbr', 'pydoc', 'rexec', 'runpy', 'shlex', 'shutil', 'SimpleHTTPServer',
                        'SimpleXMLRPCServer', 'site', 'smtpd', 'socket', 'SocketServer',
                        'subprocess', 'sysconfig', 'tabnanny', 'tarfile', 'telnetlib',
                        'tempfile', 'Tix', 'trace', 'turtle', 'urllib', 'urllib2',
                        'user', 'uu', 'webbrowser', 'whichdb', 'zipfile', 'zipimport']
    for forbid in module_blacklist:
        if name == forbid:        # don't let user import these modules
            raise RuntimeError('No you can\'t import {0}!!!'.format(forbid))
    # normal modules can be imported
    return __import__(name, *args, **kwargs)

def sandbox_filter(command):
    blacklist = ['exec', 'sh', '__getitem__', '__setitem__',
                 '=', 'open', 'read', 'sys', ';', 'os']
    for forbid in blacklist:
        if forbid in command:
            return 0
    return 1

def sandbox_exec(command):      # sandbox user input
    result = 0
    __sandboxed_builtins__ = dict(__builtins__.__dict__)
    __sandboxed_builtins__['__import__'] = _hook_import_    # hook import
    del __sandboxed_builtins__['open']
    _global = {
        '__builtins__': __sandboxed_builtins__
    }
    if sandbox_filter(command) == 0:
        print('Malicious user input detected!!!')
        exit(0)
    #command = 'result = ' + command
    try:
        print("be here 1-------------------------------------------------------------------")
        ret = exec(command, _global)    # do calculate in a sandboxed environment
        print(ret)
    except Exception as e:
        print("exception:", command)
        print(e)
        return 0
    #result = _global['result']  # extract the result
    return command

banner()
while 1:
    command = getexp()
    print(sandbox_exec(command))
