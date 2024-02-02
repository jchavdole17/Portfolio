set schema 'shopify';

begin transaction;

insert into apps (id, url, title, developer, developer_link, icon, reviews_count) 
values ('683d06af-14c7-4733-9bde-ec5b699af997', 'https://www.utexas.edu/', 'UT AUSTIN WEBSITE', 'UT AUSTIN','https://www.utexas.edu/content/about-texas',
       null, 0);
        
insert into key_benefits (app_id, title, description)
values ('683d06af-14c7-4733-9bde-ec5b699af997', 'UT AUSTIN WEBSITE', 'Main web page of UT Austin');

insert into pricing_plans (id, app_id, title, price) 
values ('961a2751-1dbd-4f0f-8248-9fe6a6efd4ac', NULL, '1 semester', 6000);

insert into pricing_plan_features (app_id, pricing_plan_id, feature) 
values ('683d06af-14c7-4733-9bde-ec5b699af997', '961a2751-1dbd-4f0f-8248-9fe6a6efd4ac', 'Free tuition');


commit;