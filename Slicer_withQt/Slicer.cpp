/*
 *qmlとスライサの兼ね合い関連
*/
#include "Slicer.h"
#include <iostream>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QAttribute>
#include <QGeometryRenderer>
#include <QObject>
#include <QVector>
#include <QList>

#include <QUrl>
#include <Qt3DRender/QBuffer>
#include <QByteArray>

#include <QPickTriangleEvent>
#include "slice_data.h"


point parse_point(const float * point_data, int index){ 
    float x = point_data[index];
    float y = point_data[index+1];
    float z = point_data[index+2];
    return point(x,y,z);
}

Qt3DRender::QGeometry* Slicer::exeSlicing(Qt3DRender::QGeometry *geometry)
{
    std::cout << "Slicing" << std::endl;
    std::cout << geometry->attributes().length() << std::endl;
    Qt3DRender::QGeometry* geometry_output = new Qt3DRender::QGeometry();

    for(int i=0; i < geometry->attributes().length(); i++)
    {
        if (geometry->attributes().at(i)->name() == Qt3DRender::QAttribute::defaultPositionAttributeName())
        {
            
            Qt3DRender::QAttribute *attribute = geometry->attributes().at(i);

            const Qt3DRender::QBuffer *buffer = attribute->buffer();
            const QByteArray &data = buffer->data();

            int vertexOffset = 0 * attribute->byteStride();
            int offset = vertexOffset + attribute->byteOffset();

            const char *rawData = &(data.data()[offset]);
            std::cout << "byte offset : " << geometry->attributes().at(i)->byteOffset() << std::endl;

            std::cout << "byte stride : " << geometry->attributes().at(i)->byteStride() << std::endl;

            // replace float with your data type
            float *vertex;
            const float *typedVertexData = reinterpret_cast<const float *>(rawData);
            slicing.mesh_triangles.triangles.clear();
            
            for (int j = 0; j < attribute->count(); j+=3)
            {
                auto v1 = parse_point(typedVertexData,j*6);
                auto v2 = parse_point(typedVertexData,(j+1)*6);
                auto v3 = parse_point(typedVertexData,(j+2)*6);
                slicing.mesh_triangles.triangles.push_back(triangle(v1,v2,v3));

            }
            std::cout << "triangle data : " << slicing.mesh_triangles.triangles.size() << std::endl;
            slicing.SliceData();

            //スライス結果をgeometryに適用する
            //Qt3DRender::QAttribute *attribute_output = new Qt3DRender::QAttribute;
            QByteArray data_output;
            uint Counter = 0;
            for(int j=0; j < slicing.layer_polygons_end.size(); j++)
            {
                for(int k =0; k < slicing.layer_polygons_end[j].size(); k++)
                {
                    for(int l=0; l < slicing.layer_polygons_end[j][k].size(); l++)
                    {
                        Counter++;
                        float x = slicing.layer_polygons_end[j][k][l].x/slicing.ACCURACY;
                        float y = slicing.layer_polygons_end[j][k][l].y/slicing.ACCURACY;
                        float z = slicing.layer_polygons_end[j][k][l].z/slicing.ACCURACY;
                        //std::cout << "x:" << x << ",y:" << y << ",z:" << z << std::endl;
                        data_output.append(reinterpret_cast<const char *>(&x), sizeof(x));
                        data_output.append(reinterpret_cast<const char *>(&y), sizeof(y));
                        data_output.append(reinterpret_cast<const char *>(&z), sizeof(z));
                    }
                }
            }
            Qt3DRender::QBuffer *buffer_output = new Qt3DRender::QBuffer;
            buffer_output->setAccessType(Qt3DRender::QBuffer::Write);
            buffer_output->setUsage(Qt3DRender::QBuffer::StaticDraw);
            buffer_output->setData(data_output);
            Qt3DRender::QAttribute *attribute_output = new Qt3DRender::QAttribute();
            attribute_output->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
            attribute_output->setBuffer(buffer_output);
            attribute_output->setVertexBaseType(Qt3DRender::QAttribute::Float);
            attribute_output->setVertexSize(3);
            attribute_output->setByteOffset(0);
            attribute_output->setByteStride(12);
            attribute_output->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
            std::cout << "Coutner:" << Counter << std::endl;
            attribute_output->setCount(Counter);
            geometry_output->addAttribute(attribute_output);
        }
    }
    return geometry_output;
}


Qt3DRender::QGeometry *Slicer::getGeometryData(Qt3DRender::QGeometry *geometry)
{
    std::cout << "get data" << std::endl;
    std::cout << geometry->attributes().length() << std::endl;
    for (int i = 0; i < geometry->attributes().length(); i++)
    {
        std::cout << "attribute type : " << geometry->attributes().at(i)->name().toStdString() << std::endl;
        std::cout << "count :" << geometry->attributes().at(i)->count() << std::endl;
        std::cout << "byte offset : " << geometry->attributes().at(i)->byteOffset() << std::endl;

        std::cout << "byte stride : " << geometry->attributes().at(i)->byteStride() << std::endl;
        //xyzrgb = 6 * 4(float size) = 24byte
        //何バイトごとに次のデータが来るか

        std::cout << "type : " << geometry->attributes().at(i)->vertexBaseType() << std::endl;
        std::cout << "vertex size: " << geometry->attributes().at(i)->vertexSize() << std::endl;
    }

    Qt3DRender::QAttribute *attribute = geometry->attributes().at(0);

    const Qt3DRender::QBuffer *buffer = attribute->buffer();
    const QByteArray &data = buffer->data();

    int vertexOffset = 0 * attribute->byteStride();
    int offset = vertexOffset + attribute->byteOffset();

    const char *rawData = &(data.data()[offset]);

    // replace float with your data type
    float *vertex;
    const float *typedVertexData = reinterpret_cast<const float *>(rawData);

    for (int i = 0; i < attribute->vertexSize(); i++)
    {
        std::cout << i << std::endl;
        std::cout << typedVertexData[i] << std::endl;
    }

    for (int i = 0; i < attribute->vertexSize(); i++)
    {
        std::cout << i << std::endl;
        std::cout << typedVertexData[i + 3] << std::endl;
    }

    return geometry;

}

Qt3DRender::QGeometry * Slicer::changeGeometryColor(Qt3DRender::QGeometry *geometry)
{
    QByteArray array;
    Qt3DRender::QAttribute *attribute = geometry->attributes().at(0);

    std::cout << "get geometry" << std::endl;
    float f_r = 0.5;
    float f_g = 0.5;
    float f_b = 0.5;
    float f_a = 1.0;

    for (int i = 0; i < geometry->attributes().length(); i++)
    {
        if (geometry->attributes().at(i)->name() == Qt3DRender::QAttribute::defaultColorAttributeName())
        {
            return geometry;
        }
    }
    for (int i = 0; i < attribute->count(); i++)
    {
        array.append(reinterpret_cast<const char *>(&f_r), sizeof(f_r));
        array.append(reinterpret_cast<const char *>(&f_g), sizeof(f_g));
        array.append(reinterpret_cast<const char *>(&f_b), sizeof(f_b));
    }

    Qt3DRender::QBuffer *buffer = new Qt3DRender::QBuffer;
    buffer->setAccessType(Qt3DRender::QBuffer::Write);
    buffer->setUsage(Qt3DRender::QBuffer::StaticDraw);
    buffer->setData(array);
    std::cout << "UsageType :" << attribute->buffer()->usage() << std::endl;
    std::cout << "Access Type : " << attribute->buffer()->accessType() << std::endl;
    std::cout << "Sync :" << attribute->buffer()->isSyncData() << std::endl;

    Qt3DRender::QAttribute *new_attribute = new Qt3DRender::QAttribute();
    new_attribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    new_attribute->setBuffer(buffer);
    new_attribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    new_attribute->setVertexSize(3);
    new_attribute->setByteOffset(0);
    new_attribute->setByteStride(12);
    new_attribute->setName(Qt3DRender::QAttribute::defaultColorAttributeName());
    new_attribute->setCount(attribute->count());

    geometry->addAttribute(new_attribute);
    

    return geometry;
}

Qt3DRender::QGeometryRenderer *Slicer::getGeometryRenderer(Qt3DRender::QGeometryRenderer *geometryRenderer, Qt3DRender::QPickTriangleEvent *pick)
{
    std::cout << "Geometry Renderer" << std::endl;
    Qt3DRender::QGeometry *geometry = geometryRenderer->geometry();
    for (int i = 0; i < geometry->attributes().length(); i++)
    {
        std::cout << "attribute type : " << geometry->attributes().at(i)->name().toStdString() << std::endl;
        std::cout << "count :" << geometry->attributes().at(i)->count() << std::endl;
        std::cout << "byte offset : " << geometry->attributes().at(i)->byteOffset() << std::endl;

        std::cout << "byte stride : " << geometry->attributes().at(i)->byteStride() << std::endl;
        //xyzrgb = 6 * 4(float size) = 24byte
        //何バイトごとに次のデータが来るか

        std::cout << "type : " << geometry->attributes().at(i)->vertexBaseType() << std::endl;
        std::cout << "vertex size: " << geometry->attributes().at(i)->vertexSize() << std::endl;
    }
    std::cout << "Triangle vertex : " <<  pick->triangleIndex() << std::endl;
    std::cout << "Triangle vertex 1 : " << pick->vertex1Index() << std::endl;

    QByteArray array;
    Qt3DRender::QAttribute *attribute = geometry->attributes().at(0);

    bool set_color_attribute = true;
    float f_r = 0.5;
    float f_g = 0.5;
    float f_b = 0.5;

    float pf_r = 0.0;
    float pf_g = 1.0;
    float pf_b = 0.0;
    float pf[3] = { pf_r, pf_g, pf_b };

    for (int i = 0; i < geometry->attributes().length(); i++)
    {
        //#すでにカラーが設定されている場合
        if (geometry->attributes().at(i)->name() == Qt3DRender::QAttribute::defaultColorAttributeName())
        {
            set_color_attribute = false;
            break;
        }
    }

    if(set_color_attribute){
        std::cout << "#### Set Color ####" << std::endl;

        for (int i = 0; i < attribute->count(); i++)
        {
            array.append(reinterpret_cast<const char *>(&f_r), sizeof(f_r));
            array.append(reinterpret_cast<const char *>(&f_g), sizeof(f_g));
            array.append(reinterpret_cast<const char *>(&f_b), sizeof(f_b));
        }
        //array.append(reinterpret_cast<const char*>(&f), sizeof(f));
        Qt3DRender::QBuffer *buffer = new Qt3DRender::QBuffer;
        buffer->setAccessType(Qt3DRender::QBuffer::Write);
        buffer->setUsage(Qt3DRender::QBuffer::StaticDraw);
        buffer->setData(array);
        buffer->setSyncData(true);
        std::cout << "UsageType :" << attribute->buffer()->usage() << std::endl;
        std::cout << "Access Type : " << attribute->buffer()->accessType() << std::endl;
        std::cout << "Sync :" << attribute->buffer()->isSyncData() << std::endl;

        Qt3DRender::QAttribute *new_attribute = new Qt3DRender::QAttribute();
        new_attribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
        new_attribute->setBuffer(buffer);
        new_attribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
        new_attribute->setVertexSize(3);
        new_attribute->setByteOffset(0);
        new_attribute->setByteStride(12);
        new_attribute->setName(Qt3DRender::QAttribute::defaultColorAttributeName());
        new_attribute->setCount(attribute->count());
        geometry->addAttribute(new_attribute);

    }



    for (int i = 0; i < geometry->attributes().length(); i++)
    {
        
        if (geometry->attributes().at(i)->name() == Qt3DRender::QAttribute::defaultColorAttributeName())
        {

            //Qt3DRender::QAttribute *attribute_data = geometry->attributes().at(i);

            //const QByteArray &data = buffer->data();

            std::cout << "##### Change Color #####" << std::endl;
            
            //TODO 最適化
            QByteArray * array_pic = new QByteArray();
            for (int j = 0; j < geometry->attributes().at(i)->count(); j++)
            {
                if(j >= pick->vertex1Index() && j <= pick->vertex3Index()){
                    array_pic->append(reinterpret_cast<const char *>(&pf_r), sizeof(pf_r));
                    array_pic->append(reinterpret_cast<const char *>(&pf_g), sizeof(pf_g));
                    array_pic->append(reinterpret_cast<const char *>(&pf_b), sizeof(pf_b));
                }else{
                    array_pic->append(reinterpret_cast<const char *>(&f_r), sizeof(f_r));
                    array_pic->append(reinterpret_cast<const char *>(&f_g), sizeof(f_g));
                    array_pic->append(reinterpret_cast<const char *>(&f_b), sizeof(f_b));
                }

            }
            geometry->attributes().at(i)->buffer()->setData(*array_pic);



            break;


        }
    }
    return geometryRenderer;
}

