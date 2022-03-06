//
// Created by Алексей Сиротин on 06.03.2022.
//

#ifndef CREACTORCORE_SRC_MONO_MAP_H
#define CREACTORCORE_SRC_MONO_MAP_H

#include "mono.h"
#include "mono_operator.h"
#include "map_subscriber.h"

template<typename IN, typename OUT>
class MonoMap : public InternalMonoOperator<IN, OUT> {
 private:
	std::function<OUT *(IN *)> _mapper;

 public:
	explicit MonoMap(Mono<IN> *source, std::function<OUT *(IN *)> mapper, QObject *parent);
	CoreSubscriber<IN> *subscribeOrReturn(CoreSubscriber<IN> *actual) override;
};

template<typename IN, typename OUT>
MonoMap<IN, OUT>::MonoMap(Mono<IN> *source, std::function<OUT *(IN *)> mapper, QObject *parent)
	: _mapper(mapper), InternalMonoOperator<IN, OUT>(source, parent) {

}

template<typename IN, typename OUT>
CoreSubscriber<IN> *MonoMap<IN, OUT>::subscribeOrReturn(CoreSubscriber<IN> *actual) {
	return new MapSubscriber<IN, OUT>(actual, _mapper);
}

#endif //CREACTORCORE_SRC_MONO_MAP_H