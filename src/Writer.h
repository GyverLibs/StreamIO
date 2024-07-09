#pragma once
#include <Arduino.h>

class Writer {
   public:
    Writer(Stream& stream) : _stream(&stream) {}
    Writer(uint8_t* buffer) : _buffer(buffer) {}

    void write(const void* data, size_t size) {
        if (_stream) {
            _writed += _stream->write((const uint8_t*)data, size);
        } else if (_buffer) {
            memcpy(_buffer, data, size);
            _buffer += size;
            _writed += size;
        }
    }

    template <typename T>
    void write(T& val) {
        write(&val, sizeof(T));
    }

    size_t writed() {
        return _writed;
    }

   private:
    Stream* _stream = nullptr;
    uint8_t* _buffer = nullptr;
    size_t _writed = 0;
};