#pragma once
#include "Core/Containers/ArrayView.h"
#include "Core/Containers/DynamicArray.h"
#include "TangentPoint.h"

namespace Hydro
{
    template<typename TangentPoint>
    class BezierCurve
    {
    public:
        using SizeType = typename Array<TangentPoint>::SizeType;
        using VectorType = typename TangentPoint::VectorType;
        
        BezierCurve() = default;
        virtual ~BezierCurve() = default;

        void AddPoint(const TangentPoint& Point)
        {
            m_TangentPoints.Add(Point);
        }
        
        void AddPoints(const ArrayView<TangentPoint>& Points)
        {
            m_TangentPoints.AddRange(Points.Data(), Points.Count());
        }
        
        TangentPoint& GetPoint(SizeType Index)
        {
            HYDRO_ASSERT(Index < m_TangentPoints.Count(), "Index out of bounds!");
            return m_TangentPoints[Index];
        }

        const TangentPoint& GetPoint(SizeType Index) const
        {
            HYDRO_ASSERT(Index < m_TangentPoints.Count(), "Index out of bounds!");
            return m_TangentPoints[Index];
        }
        
        void SetPoint(SizeType Index, const TangentPoint& Point)
        {
            HYDRO_ASSERT(Index < m_TangentPoints.Count(), "Index out of bounds!");
            m_TangentPoints[Index] = Point;
        }

        void RemoveAt(SizeType Index)
        {
            m_TangentPoints.RemoveAt(Index);
        }

        void Remove(const TangentPoint& Point)
        {
            m_TangentPoints.Remove(Point);
        }

        TangentPoint& First()
        {
            return m_TangentPoints.First();
        }

        TangentPoint& Last()
        {
            return m_TangentPoints.Last();
        }

        virtual VectorType SamplePoint(f32 Value) const = 0;
        
    protected:
        Array<TangentPoint> m_TangentPoints;
    };

    class BezierCurve2D : public BezierCurve<TangentPoint2D>
    {
    public:
        Vector2 SamplePoint(f32 Value) const override;
    };
}
