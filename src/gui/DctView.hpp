#ifndef HSTEFAN_DCT_VIEW_HPP
#define HSTEFAN_DCT_VIEW_HPP

#include <SCV/Canvas.h>
#include <SCV/Kernel.h>
#include <vector>
#include <utility>
#include <iostream>
#include "../dct/DCT.hpp"

namespace hstefan
{
   namespace gui
   {
      template <class T>
      class DctView : public scv::Canvas
      {
      public:
         typedef std::pair<unsigned int, unsigned int> vertex_type;
         static const unsigned int COMPONENT_SPACING_X = 10;
         static const unsigned int COMPONENT_SPACING_Y = 10;
         static const unsigned int SQUARE_LENGTH = 3;

         DctView(const scv::Point& pi, const scv::Point& pf, 
            const std::vector<T>& coef = std::vector<T>(), bool middle_based = true);
         void render();
         void setCoefficients(const std::vector<T>& coef);

         virtual void onMouseOver(const scv::MouseEvent &evt);

         inline scv::Label* getLabel();

      protected:
         int overSquare(scv::Point pos, unsigned int square_l = SQUARE_LENGTH);

         std::vector<vertex_type> vertex_buffer;
         std::vector<T> original;
         bool middle;
         scv::Label val_label;
         T max;
      };

      template <class T>
      DctView<T>::DctView(const scv::Point& pi, const scv::Point& pf, 
         const std::vector<T>& coef, bool middle_based)
         : scv::Canvas(pi, pf), vertex_buffer(), middle(middle_based), original(), val_label(scv::Point(0, 0), ""), 
         max(0)
      {
         setCoefficients(coef);
      }

      template <class T>
      void DctView<T>::render()
      {
         glClearColor(1.0, 1.0, 1.0, 1.0);
         glClear(GL_COLOR_BUFFER_BIT);

         glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

         glColor3f(1.0f, 0.f, 0.f);
         glBegin(GL_LINE_STRIP);
         for(std::vector<vertex_type>::const_iterator it = vertex_buffer.begin(); it != vertex_buffer.end(); ++it)
            glVertex2i((*it).first, (*it).second);
         glEnd();

         glBegin(GL_QUADS);
         glColor3f(1.f, 0.f, 0.f);
         for(std::vector<vertex_type>::const_iterator it = vertex_buffer.begin(); it != vertex_buffer.end(); ++it)
         {	
            glVertex2i((*it).first - SQUARE_LENGTH, (*it).second + SQUARE_LENGTH);
            glVertex2i((*it).first + SQUARE_LENGTH, (*it).second + SQUARE_LENGTH);
            glVertex2i((*it).first + SQUARE_LENGTH, (*it).second - SQUARE_LENGTH);
            glVertex2i((*it).first - SQUARE_LENGTH, (*it).second - SQUARE_LENGTH);
         }
         glEnd();

         if(middle)
         {
            glLineWidth(.5f);
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(6, 0xAAAA); //linha tracejada
            glBegin(GL_LINE_STRIP);
            glColor3f(0.f, 0.f, 0.f);
            glVertex2i(0, getHeight()/2);
            glVertex2i(getWidth(), getHeight()/2);
            glEnd();

            glDisable(GL_LINE_STIPPLE);
         }
         glDisable(GL_LINE_SMOOTH_HINT);
      }

      template <class T>
      void DctView<T>::setCoefficients(const std::vector<T>& coef)
      {
         original.resize(coef.size());
         original = coef;
         vertex_buffer.clear();
         unsigned int x = 10;
         unsigned int div = middle ? 2 : 1;
         const unsigned int ratio = getWidth()/coef.size() + 2*COMPONENT_SPACING_X/coef.size();
         max = 0;
         for(std::vector<T>::const_iterator it = coef.begin(); it != coef.end(); ++it)
         {
            if (abs(*it) > max) 
               max = abs(*it);
         }
         int height = getHeight();
         float max_f = (float)max;
         float scale = ((height - 10)/div)/max_f;
         
         for(std::vector<T>::const_iterator it = coef.begin(); it != coef.end(); ++it)
         {
            vertex_buffer.push_back( vertex_type(x, 
               (unsigned int)(-scale * (*it) + height/div) ));
            //x = scale
            //y = (*it)
            //z = height
            //w = div
            // -xy + z/w

            //(z/w - y)/x
            std::cout << toNumber(*it) << "," <<  toNumber((T)((height/div) - vertex_buffer.back().second)/scale)
                << std::endl;
            x += ratio;
         }
      }

      template <class T>
      void DctView<T>::onMouseOver(const scv::MouseEvent &evt)
      {
         int sq = overSquare(evt.getPosition());
         if(sq >= 0)
         {
            scv::Point lab_pos = evt.getPosition() + getRelativePosition() - scv::Point(15, 15);

            val_label.setRelativePosition(lab_pos);

            if(!val_label.isVisible())
               val_label.setVisible(true);

            std::ostringstream stream;
            stream << toNumber(original[sq]);
            val_label.setString(stream.str());
         }
         else if (val_label.isVisible())
         {
            val_label.setVisible(false);
         }
      }

      inline double toNumber(double x)
      {
         return x;
      }

      inline unsigned int toNumber(unsigned char x)
      {
         return (unsigned int)x;
      }

      inline int toNumber(char x)
      {
         return (int)x;
      }

      template <class T>
      int DctView<T>::overSquare(scv::Point pos, unsigned int square_l)
      {
         vertex_type aux;
         int i = 0;
         for(std::vector<vertex_type>::iterator it = vertex_buffer.begin(); it != vertex_buffer.end(); ++it, ++i)
         {
            aux = *it;
            if(pos.x >= (int)(aux.first - square_l) && pos.y >= (int)(aux.second - square_l)
               && pos.x <= (int)(aux.first + square_l) && pos.y <= (int)(aux.second + square_l))
            {
               if(label)
               {
                  std::ostringstream stream;
                  stream << toNumber(original[i]);
                  val_label.setString(stream.str());
               }
               else
               {
                  (*it).second = pos.y;
               }
               return i;
            }
         }
         return -1;
      }

      template <class T>
      scv::Label* DctView<T>::getLabel()
      {
         return &val_label;
      }
   }
}

#endif