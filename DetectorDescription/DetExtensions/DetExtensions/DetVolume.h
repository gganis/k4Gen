//
//  DetVolume.h
//  
//
//  Created by Julia Hrdinka on 09/01/15.
//
//

#ifndef DET_DETVOLUME_H
#define DET_DETVOLUME_H

#include "DetExtensions/IDetExtension.h"

namespace DD4hep {
    namespace Geometry {
        class DetElement;
    }
}

namespace Det {
    
    class DetVolume : public IDetExtension {
    
    public:
        
        DetVolume()
        {}
        DetVolume(const DetVolume, const DD4hep::Geometry::DetElement&)
        {}
        virtual ~DetVolume()
        {}
    };
}

#endif //DET_DETVOLUME_H
