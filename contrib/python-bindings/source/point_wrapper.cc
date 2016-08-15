// ---------------------------------------------------------------------
//
// Copyright (C) 2016 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE at
// the top level of the deal.II distribution.
//
// ---------------------------------------------------------------------

#include <point_wrapper.h>

#ifdef DEAL_II_WITH_CXX11

#include <deal.II/base/point.h>

DEAL_II_NAMESPACE_OPEN

namespace python
{
  PointWrapper::PointWrapper()
    :
    dim(-1),
    point(nullptr)
  {}


  PointWrapper::PointWrapper(boost::python::list coord)
  {
    dim = boost::python::len(coord);
    if (dim == 2)
      point = new Point<2> (boost::python::extract<double>(coord[0]),
                            boost::python::extract<double>(coord[1]));
    else if (dim == 3)
      point = new Point<3> (boost::python::extract<double>(coord[0]),
                            boost::python::extract<double>(coord[1]),
                            boost::python::extract<double>(coord[2]));
    else
      AssertThrow(false,
                  ExcMessage("The list of coordinates must contain two or three elements."));
  }



  PointWrapper::PointWrapper(const PointWrapper &other)
  {
    copy(other);
  }



  PointWrapper::~PointWrapper()
  {
    clear();
    dim = -1;
  }



  PointWrapper &PointWrapper::operator= (const PointWrapper &other)
  {
    clear();
    copy(other);

    return *this;
  }



  double PointWrapper::get_x() const
  {
    if (dim == 2)
      return (*static_cast<Point<2>*>(point))(0);
    else
      return (*static_cast<Point<3>*>(point))(0);
  }



  void PointWrapper::set_x(double x)
  {
    if (dim == 2)
      (*static_cast<Point<2>*>(point))(0) = x;
    else
      (*static_cast<Point<3>*>(point))(0) = x;
  }



  double PointWrapper::get_y() const
  {
    if (dim == 2)
      return (*static_cast<Point<2>*>(point))(1);
    else
      return (*static_cast<Point<3>*>(point))(1);
  }



  void PointWrapper::set_y(double y)
  {
    if (dim == 2)
      (*static_cast<Point<2>*>(point))(1) = y;
    else
      (*static_cast<Point<3>*>(point))(1) = y;
  }



  double PointWrapper::get_z() const
  {
    if (dim == 3)
      return (*static_cast<Point<3>*>(point))(2);
    else
      AssertThrow(false,
                  ExcMessage("The z coordinate is only available for three-dimensional points"));
    // Silence a warning
    return 0.;
  }



  void PointWrapper::set_z(double z)
  {
    if (dim == 3)
      (*static_cast<Point<3>*>(point))(2) = z;
    else
      AssertThrow(false,
                  ExcMessage("The z coordinate is only available for three-dimensional points"));
  }




  void PointWrapper::clear()
  {
    if (point != nullptr)
      {
        if (dim == 2)
          {
            // We cannot call delete on a void pointer so cast the void pointer back
            // first.
            Point<2> *tmp = static_cast<Point<2>*>(point);
            delete tmp;
          }
        else
          {
            Point<3> *tmp = static_cast<Point<3>*>(point);
            delete tmp;
          }
        point = nullptr;
      }
  }



  void PointWrapper::copy(const PointWrapper &other)
  {
    dim = other.dim;

    AssertThrow(other.point != nullptr,
                ExcMessage("Underlying point does not exist."));

    if (dim == 2)
      {
        Point<2> *other_point = static_cast<Point<2>*>(other.point);
        point = new Point<2> ((*other_point)[0], (*other_point)[1]);
      }
    else if (dim == 3)
      {
        Point<3> *other_point = static_cast<Point<3>*>(other.point);
        point = new Point<3> ((*other_point)[0], (*other_point)[1], (*other_point)[2]);
      }
    else
      AssertThrow(false,
                  ExcMessage("The dimension of the point should be 2 or 3."));
  }
}

DEAL_II_NAMESPACE_CLOSE

#endif
