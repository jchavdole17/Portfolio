printjson("****************************************************************");
printjson("1) Samples with elevation between 7000-8000 or SeaSurfaceTemperature above 10");
printjson(db.data.find({"$or": [{"elevation": {"$gte": 7000, "$lte":8000}}, {"seaSurfaceTemperature.value":{"$gte":10}}]},{"elevation":1,"seaSurfaceTemperature":1}).sort({"SeaSurfaceTemperature":1}).limit(5));


printjson("****************************************************************");
printjson("2) Samples with visbility between 1000-10000 and totalCoverage greater than or equal to 9");
printjson(db.data.find({"visibility.distance.value":{"$gt":1000,"$lt": 10000}, "skyConditionObservation.totalCoverage.value":{"$gte":"09"}},{"visibility.distance.value":1, "skyConditionObservation.totalCoverage.value":1}).sort({"visibility.distance.value":1}).limit(5));

printjson("****************************************************************");
printjson("3) Samples with section 'SA1' and a temperature value greater than 20");
printjson(db.data.find({"sections": "SA1", "airTemperature.value": {"$gte": 20}},{"sections":1, "airTemperature.value":1}).sort({"airTemperature.value":1}).limit(5));

printjson("****************************************************************");
printjson("4) Past weather atmospheric condition with a value of 9");
printjson(db.data.find({pastWeatherObservationManual: {$elemMatch: {"atmosphericCondition.value":"9"}}},{"pastWeatherObservationManual.atmosphericCondition.value": 1, "elevation": 1}).limit(5))

printjson("****************************************************************");
printjson("5) Pressure value is less than 500 or wind speed rate is less than 10");
printjson(db.data.find({"$or":[{"pressure.value": {"$lt": 500}}, {"wind.speed.rate": {"$lt":10}}]},{"pressure.value":1, "wind.speed":1}).limit(5));

printjson("****************************************************************");
printjson("6) Find samples where the section AY1 is not present");
printjson(db.data.find({sections: {"$ne":"AY1"}},{sections:1}).limit(5));

printjson("****************************************************************");
printjson("7) Find samples where both coordinates are between 0 and 50");
printjson(db.data.find({"position.coordinates.0": {"$gte":0, "$lte": 50}, "position.coordinates.1": {"$gte":0, "$lte": 50}},{"position":1}).limit(5));

printjson("****************************************************************");
printjson("8) Find samples with wave heights between 10 and 20, and with wind speed rates between 10 and 100");
printjson(db.data.find({"waveMeasurement.waves.height": {"$gte": 10, "$lte": 20}, "wind.speed.rate":{"$gte": 10, "$lte":100}},{"waveMeasurement.waves.height":1, "wind.speed":1}).sort({"waveMeasurement.waves.height":1}).limit(5));

printjson("****************************************************************");
printjson("9) Find documents with present weather condition of '05' and an x coordinate position greater than 50");
printjson(db.data.find({"presentWeatherObservationManual": {$elemMatch: {condition: "05"}}, "position.coordinates.0": {"$gt":50}}, {"presentWeatherObservationManual": 1, "position.coordinates":1}).sort({"position.coordinates.0": 1}).limit(5))

printjson("****************************************************************");
printjson("10) Return documents with precipitation water depth greater than 0 or a wind speed rate larger than 10");
printjson(db.data.find({"$or":[{"precipitationEstimatedObservation.estimatedWaterDepth": {"$gt": 0}},{"wind.speed.rate": {"$gte": 10}}]}, {"precipitationEstimatedObservation.estimatedWaterDepth":1, "wind.speed.rate":1}).sort({"wind.speed.rate":1, "precipitationEstimatedObservation.estimatedWaterDepth": 1}).limit(5));