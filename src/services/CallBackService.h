#ifndef CALLBACK_SERVICE
#define CALLBACK_SERVICE

template <typename T>

class CallBackService
{

    void (*_cb)(T);

protected:
    void dispatchEvent(T value)
    {
        _cb(value);
    }

public:
    void onEvent(void (*cb)(T))
    {
        _cb = cb;
    }
};

#endif