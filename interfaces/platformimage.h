#ifndef PLATFORMIMAGE_H
#define PLATFORMIMAGE_H

namespace Wt {

class PlatformImage
{
public:
    virtual ~PlatformImage() {}

    virtual void* platformImageStruct() const = 0;
};

}

#endif
