// 
// Created by Balajanovski on 29/09/2018.
//

#ifndef TEAPOT_DEMO_NOCOPY_H
#define TEAPOT_DEMO_NOCOPY_H

struct NoCopy {
    NoCopy() = default;
    NoCopy(NoCopy const &) = delete;
    NoCopy &operator = (NoCopy const &) = delete;
};

#endif //TEAPOT_DEMO_NOCOPY_H
