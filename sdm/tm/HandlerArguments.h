#ifndef _HANDLER_ARGUMENTS_H_
#define _HANDLER_ARGUMENTS_H_

// A simple class for passing "multiple" arguments into threads.
class HandlerArguments {
public:
    HandlerArguments(void *buf, size_t bufLen, unsigned long senderHost = 0, unsigned long senderPort = 0) :
        _buf(new char[bufLen]), _bufLen(bufLen), _senderHost(senderHost), _senderPort(senderPort)
    {
        if (_buf != NULL)
            memcpy(_buf, buf, bufLen);
    }

    ~HandlerArguments()
    {
        if (_buf != NULL)
            delete[] _buf;
    }
    // Declared, but not defined, fixes warning
    HandlerArguments(const HandlerArguments& right);
    HandlerArguments& operator=(const HandlerArguments& right);
    
    const char*   getBuffer() const     { return _buf; }
    size_t        getBufferSize() const { return _bufLen; }
    unsigned long getSenderHost() const { return _senderHost; }
    unsigned long getSenderPort() const { return _senderPort; }

private:
    char*          _buf;
    size_t         _bufLen;
    unsigned long  _senderHost;
    unsigned long  _senderPort;
};

#endif
