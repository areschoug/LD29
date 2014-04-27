//
//  Defines.h
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#ifndef beneath_the_surface_Defines_h
#define beneath_the_surface_Defines_h



#define kSkyBackgroundColor4B Color4B(154.0,180.0,240.0, 255.0)
#define kWaterBackgroundColor3B Color3B(61.0,95.0,183.0)

#define kZBackground -101
#define kZWaterBackground -100
//place stuff here
#define kZRod -1
#define kZWaterForeground 100


#define kSpriteScaleFactor 4

#endif

static inline float map(float x, float in_min, float in_max, float out_min, float out_max) {
    return (((x) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min));
}
