/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#pragma once

/**
 * @file   Board3DTo2D.h
 * @author Martial Tola <http://liris.cnrs.fr/martial.tola/>
 * @date   mercredi 22 juin 2011
 * 
 * @brief
 *
 * Header file for module Board3DTo2D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Board3DTo2D_RECURSES)
#error Recursive header files inclusion detected in Board3DTo2D.h
#else // defined(Board3DTo2D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Board3DTo2D_RECURSES

#if !defined Board3DTo2D_h
/** Prevents repeated inclusion of headers. */
#define Board3DTo2D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/io/Display3D.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/io/Color.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{


/////////////////////////////////////////////////////////////////////////////
// class Board3DTo2D
/**
 * Description of class 'Board3DTo2D' <p>
 * @brief Class for PDF, PNG, PS, EPS, SVG export drawings with 3D->2D projection.
 */
  class Board3DTo2D : public Display3D
{
public:
  /**
   * Cairo type for save files.
   */
  enum CairoType { CairoPDF, CairoPNG, CairoPS, CairoEPS, CairoSVG };
  
  /*!
   * \brief Constructor.
   */
  Board3DTo2D();
  
  
  ~Board3DTo2D(){};
  

  /**
    * @return the style name used for drawing this object.
    */
  std::string styleName() const
  {
    return "Board3DTo2D";
  }
  
  /**
  * Set camera position.
  * @param x x position.
  * @param y y position.
  * @param z z position.
  */
  void setCameraPosition(double x, double y, double z) { camera_position[0] = x; camera_position[1] = y; camera_position[2] = z; }
  
  /**
  * Set camera direction.
  * @param x x direction.
  * @param y y direction.
  * @param z z direction.
  */
  void setCameraDirection(double x, double y, double z) { camera_direction[0] = x; camera_direction[1] = y; camera_direction[2] = z; }
  
  /**
  * Set camera up-vector.
  * @param x x coordinate of up-vector.
  * @param y y coordinate of up-vector.
  * @param z z coordinate of up-vector.
  */
  void setCameraUpVector(double x, double y, double z) { camera_upVector[0] = x; camera_upVector[1] = y; camera_upVector[2] = z; }
  
  /**
  * Set near and far distance.
  * @param near near distance.
  * @param far far distance.
  */
  void setNearFar(double near, double far) { ZNear = near; ZFar = far; }
  
  /**
  * Save a Cairo image.
  * @param filename filename of the image to save.
  * @param type type of the image to save (CairoPDF, CairoPNG, CairoPS, CairoEPS, CairoSVG).
  * @param width width of the image to save.
  * @param height height of the image to save.
  */
  void saveCairo(const char *filename, CairoType type, int width, int height);
  
  /**
   * The associated map type for storing possible modes used for
   * displaying for digital objects.
   */
  //typedef std::map< std::string, std::string > ModeMapping;

 //  /**
//    * The associated map type for storing the default styles of
//    * digital objects.
//    */
//   typedef std::map< std::string,CountedPtr<DrawableWithDisplay3D> > StyleMapping;
  
  DGtal::Color myDefaultColor;	//!< default color

  
  /**
   * Used to create a new list containing new Voxel objects
   * (useful to use transparency between different objects).
   * 
   **/  
  void createNewVoxelList(bool depthTest=true);
  
  /**
   * Used to create a new list containing new Line objects
   * (useful to use transparency between different objects).
   * 
   **/  
  void createNewLineList();

  /**
   * Used to create a new list containing new Point objects
   * (useful to use transparency between different objects).
   * 
   **/  
  void createNewPointList();

 
  /**
   * Set the default color for future drawing.
   *
   * @param aColor: a DGtal::Color (allow to set a trasnparency value).
   *
   **/  
  Board3DTo2D & operator<<(const DGtal::Color & aColor);



  /**
   * Draws the drawable [object] in this board. It should satisfy
   * the concept CDrawableWithDisplay3D, which requires for instance a
   * method selfDraw( Board3DTo2D & ).
   *
   * @param object any drawable object.
   * @return a reference on 'this'.
   */
  template <typename TDrawableWithDisplay3D>
  Board3DTo2D & operator<<( const  TDrawableWithDisplay3D & object );

public:
  
    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

public:
  

    // ------------------------- Private Datas --------------------------------
private:
 
  
  
  /**
   * Precompute 4x4 projection matrix for 3D->2D projection.
   */
  void precompute_projection_matrix();
  
  /**
  * Project a 3d point (3D->2D).
  * @param x3d x position of the 3d point.
  * @param y3d y position of the 3d point.
  * @param z3d z position of the 3d point.
  * @param x2d x destination projection position of the 2d point.
  * @param y2d y destination projection position of the 2d point.
  */
  void project(double x3d, double y3d, double z3d, double &x2d, double &y2d);
  
  int Viewport[4];		//!< 2D viewport
  double matrix[16]; 		//!< projection matrix
      
  double camera_position[3];	//!< camera position
  double camera_direction[3];	//!< camera direction
  double camera_upVector[3];	//!< camera up-vector
  
  double ZNear;			//!< znear distance
  double ZFar;			//!< zfar distance
  
protected :
  /*!
   * \brief init function (should be in Constructor).
  */
  virtual void init();

private:

  }; // end of class Board3DTo2D
  
  /**
   * Cairo3dCameraPosition class to set camera position.
   */
  struct Cairo3dCameraPosition : public DrawWithDisplay3DModifier
  {
    /**
     * Constructor.
     *
     * @param x x position.
     * @param y y position.
     * @param z z position.
     */
    Cairo3dCameraPosition( const double x, const double y, const double z )
    {
      eyex=x; eyey=y; eyez=z;
    }
    
    void selfDrawDisplay3D( Display3D & display) const
    {
      display.setCameraPosition(eyex, eyey, eyez);
    }
    
    private:
      double eyex, eyey, eyez;
  };
  
  /**
   * Cairo3dCameraDirection class to set camera direction.
   */
  struct Cairo3dCameraDirection : public DrawWithDisplay3DModifier
  {
    /**
     * Constructor.
     *
     * @param x x direction.
     * @param y y direction.
     * @param z z direction.
     */
    Cairo3dCameraDirection( const double x, const double y, const double z )
    {
      dirx=x; diry=y; dirz=z;
    }
    
    virtual void selfDrawDisplay3D( Display3D & display) const
    {
      display.setCameraDirection(dirx, diry, dirz);
    }
    
    private:
      double dirx, diry, dirz;
  };
  
  /**
   * Cairo3dCameraUpVector class to set camera up-vector.
   */
  struct Cairo3dCameraUpVector : public DrawWithDisplay3DModifier
  {
    /**
     * Constructor.
     *
     * @param x x coordinate of up-vector.
     * @param y y coordinate of up-vector.
     * @param z z coordinate of up-vector.
     */
    Cairo3dCameraUpVector( const double x, const double y, const double z )
    {
      upx=x; upy=y; upz=z;
    }
    
    virtual void selfDrawDisplay3D( Display3D & viewer) const
    {
      viewer.setCameraUpVector(upx, upy, upz);
    }
    
    private:
      double upx, upy, upz;
  };
  
  /**
   * Cairo3dCameraZNearFar class to set near and far distance.
   */
  struct Cairo3dCameraZNearFar : public DrawWithDisplay3DModifier
  {
    /**
     * Constructor.
     *
     * @param near near distance.
     * @param far far distance.
     */
    Cairo3dCameraZNearFar( const double near, const double far )
    {
      ZNear=near; ZFar=far;
    }
    
    virtual void selfDrawDisplay3D( Display3D & viewer) const
    {
      viewer.setNearFar(ZNear, ZFar);
    }
    
    private:
      double ZNear, ZFar;
  };

 

  
/**
 * Overloads 'operator<<' for displaying objects of class 'Board3DTo2D'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'Board3DTo2D' to write.
 * @return the output stream after the writing.
 */
std::ostream&
operator<< ( std::ostream & out, const Board3DTo2D & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/boards/Board3DTo2D.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Board3DTo2D_h

#undef Board3DTo2D_RECURSES
#endif // else defined(Board3DTo2D_RECURSES)
