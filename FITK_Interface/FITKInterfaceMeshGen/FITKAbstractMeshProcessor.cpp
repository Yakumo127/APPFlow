﻿#include "FITKAbstractMeshProcessor.h"

Interface::FITKAbstractMeshProcessor::~FITKAbstractMeshProcessor()
{
    //纯虚函数
}

void Interface::FITKAbstractMeshProcessor::setArgs(const QStringList & args)
{
    _args = args;
}

void Interface::FITKAbstractMeshProcessor::start(QStringList info /*= QStringList()*/)
{
    //纯虚函数
}

void Interface::FITKAbstractMeshProcessor::insertDataObject(QString key, Core::FITKAbstractDataObject* value)
{
    _dataObject.insert(key, value);
}

