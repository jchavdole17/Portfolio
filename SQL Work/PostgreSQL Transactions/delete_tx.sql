set schema 'shopify';

begin transaction;

/* delete foreign keys first if trying to delete primary key row*/

delete from key_benefits where app_id = '94e751e2-eb8f-42c1-810d-bddb71ed6cbd'; /*Improve order size*/

delete from pricing_plan_features where app_id = '94e751e2-eb8f-42c1-810d-bddb71ed6cbd'; /*Bulk Cancel Orders*/
       
delete from pricing_plans where app_id = '94e751e2-eb8f-42c1-810d-bddb71ed6cbd'; /*ALWAYS FREE*/

delete from apps_categories where app_id = '94e751e2-eb8f-42c1-810d-bddb71ed6cbd';  /*26a72de0d02e0e4e5f615332d61a878e*/

delete from apps where id = '94e751e2-eb8f-42c1-810d-bddb71ed6cbd';  /*26a72de0d02e0e4e5f615332d61a878e*/


commit;

