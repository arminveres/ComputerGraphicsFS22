//
//  viewModule.h
//  CubeViewer
//
//  Created by Renato Pajarola.
//
//

#ifndef  VIEWMODULE_H
#define  VIEWMODULE_H

#ifdef __cplusplus
extern "C" {
#endif

#define IMAGE_WIDTH  512
#define IMAGE_HEIGHT 512

typedef struct{
	float fieldOfView;
	float aspect;
	float nearPlane;
	float farPlane;
}perspectiveData;

#ifdef __cplusplus
}
#endif

#endif /* defined(VIEWMODULE_H) */
