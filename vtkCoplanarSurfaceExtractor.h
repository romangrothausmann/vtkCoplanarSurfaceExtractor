// .NAME vtkCoplanarSurfaceExtractor - boolean intersection operation on coplanar regions of two polydata meshes

// .SECTION Description
// vtkCoplanarSurfaceExtractor does boolean intersection operation on coplanar regions of two polydata meshes
// i.e. it extracts those surfaces of two input vtkPolyData that are coplanar
// even if e.g. two triangles are not coincident but are coplanar and overlap
// the filter will create a new triangulated polygon of the coplanar region


#ifndef __vtkCoplanarSurfaceExtractor_h
#define __vtkCoplanarSurfaceExtractor_h

#include "vtkFiltersCoreModule.h" // For export macro
#include "vtkPolyDataAlgorithm.h"

#define VTK_USE_DELAUNAY2D 0
#define VTK_USE_CONVEXHULL2D 1

class VTKFILTERSCORE_EXPORT vtkCoplanarSurfaceExtractor : public vtkPolyDataAlgorithm
{
public:
  static vtkCoplanarSurfaceExtractor *New();
  vtkTypeMacro(vtkCoplanarSurfaceExtractor,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set tolerance for face displacement
  vtkSetMacro(DistanceTolerance,double);
  vtkGetMacro(DistanceTolerance,double);

  // Description:
  // Set tolerance for face mis-orientation
  vtkSetMacro(FaceOrientationTolerance,double);
  vtkGetMacro(FaceOrientationTolerance,double);

  // Description:
  // Set tolerance for line mis-orientation
  vtkSetMacro(LineOrientationTolerance,double);
  vtkGetMacro(LineOrientationTolerance,double);

  // Description:
  // Specify whether to use vtkDelaunay2D or vtkConvexHull2D for meshing polygons
  vtkSetMacro(MeshMode,int);
  vtkGetMacro(MeshMode,int);
  void SetMeshModeToUseVector() {this->SetMeshMode(VTK_USE_DELAUNAY2D);};
  void SetMeshModeToUseNormal() {this->SetMeshMode(VTK_USE_CONVEXHULL2D);};
  const char *GetMeshModeAsString();

  // Description:
  // Set/get the desired precision for the output types. See the documentation
  // for the vtkAlgorithm::DesiredOutputPrecision enum for an explanation of
  // the available precision settings.
  vtkSetMacro(OutputPointsPrecision,int);
  vtkGetMacro(OutputPointsPrecision,int);

protected:
  vtkCoplanarSurfaceExtractor();
  ~vtkCoplanarSurfaceExtractor() {}

  virtual int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  virtual int FillInputPortInformation(int port, vtkInformation *info);
  double DistanceTolerance, FaceOrientationTolerance, LineOrientationTolerance;
  int MeshMode; // Orient/scale via normal or via vector data
  int OutputPointsPrecision;

private:
  vtkCoplanarSurfaceExtractor(const vtkCoplanarSurfaceExtractor&);  // Not implemented.
  void operator=(const vtkCoplanarSurfaceExtractor&);  // Not implemented.

  int are_coincident(double x[3], double y[3]);
  double angle_in_deg(double a[3], double b[3]);
  double angle_in_deg(double a0[3], double a1[3], double b0[3], double b1[3]);
  double angle_in_deg_unori(double a[3], double b[3]);
  double angle_in_deg_unori(double a0[3], double a1[3], double b0[3], double b1[3]);
  int point_in_both_cells(double p0[3], vtkCell *cell0, vtkCell *cell1, double d_tol);
  void z_normal_of_3points(double a0[3], double a1[3], double a2[3], double n[3], double &angle, double N[3]);


};

// Description:
// Return the vector mode as a character string.
inline const char *vtkCoplanarSurfaceExtractor::GetMeshModeAsString(void)
{
  if ( this->MeshMode == VTK_USE_DELAUNAY2D)
    {
    return "Using vtkDelaunay2D.";
    }
  else if ( this->MeshMode == VTK_USE_CONVEXHULL2D)
    {
    return "Using vtkConvexHull2D.";
    }
  else
    {
    return "Unknown";
    }
}
#endif