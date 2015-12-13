using namespace std;

#include "plan.h"
#include "utils.h"

Plan::Plan(Application_ptr &app, Specification &spec)
{
	_app = app;
	_spec = spec;
	_build();
}

void Plan::_build()
{
	switch (_spec.Side)
	{
	case SIDE_LEFT:
		// Build left
		_opts[0] = _build(_app->left(), _app->right(), Entity2D::FIT2D_RIGHT);
		break;

	case SIDE_RIGHT:
		// Build right
		_opts[1] = _build(_app->right(), _app->left(), Entity2D::FIT2D_LEFT);
		break;

	default:
		// Build both
		_opts[0] = _build(_app->left(), _app->right(), Entity2D::FIT2D_LEFT);
		_opts[1] = _build(_app->right(), _app->left(), Entity2D::FIT2D_RIGHT);
		break;
	}
}

Feature2Ds_ptr Plan::_build(Edges_ptr &act, Edges_ptr &pass, Entity2D::Fit2D fit)
{
	Feature2Ds_ptr fs = Feature2Ds::create();

	_buildLines(fs, act, pass, fit);
	_checkLines(fs);
	_optimiseLines(fs);

	if (fs->size() < 2)
	{
		_buildRads(fs, pass);
		_checkRads(fs);
		_optimiseRads(fs);
	}

	return fs;
}

void Plan::_buildLines(Feature2Ds_ptr &fs, Edges_ptr &act,
					   Edges_ptr &pass, Entity2D::Fit2D fit)
{
	Edge_ptr e = act->first();
	Feature2DLine_ptr b = Feature2DLine::create(e, pass, fit);
	fs->add((Feature2D_ptr)b);

	for (int i = 1; i < act->size(); i++)
	{
		e = act->get(i);

		// Attempt to add edge to current line
		if (! b->append(e))
		{
			// Create new line
			fs->add((Feature2D_ptr)Feature2DLine::create(e, pass, fit));
		}
	}
}

void Plan::_checkLines(Feature2Ds_ptr &fs)
{
	//TODO: implement method
}

void Plan::_optimiseLines(Feature2Ds_ptr &fs)
{
	//TODO: implement method
}

void Plan::_buildRads(Feature2Ds_ptr &fs, Edges_ptr &pass)
{
	Feature2DLine_ptr l[2];
	Feature2DRad_ptr r;
	for (int i = 0; i < fs->size() - 1; i++)
	{
		l[0] = Feature2DLine::cast(fs->get(i));
		l[1] = Feature2DLine::cast(fs->get(i + 1));
		r = Feature2DRad::create(l[0], l[1], pass);
		fs->insert((Feature2D_ptr)r, i + 1);
	}
}

void Plan::_checkRads(Feature2Ds_ptr &fs)
{
	//TODO: implement method
}

void Plan::_optimiseRads(Feature2Ds_ptr &fs)
{
	//TODO: implement method
}

Plan_ptr Plan::create(Application_ptr &app, Specification &spec)
{
	return Plan_ptr(new Plan(app, spec));
}

PlanBuilderSnapshot::PlanBuilderSnapshot()
{

}

PlanBuilderSnapshot_ptr PlanBuilderSnapshot::create()
{
	return PlanBuilderSnapshot_ptr(new PlanBuilderSnapshot());
}