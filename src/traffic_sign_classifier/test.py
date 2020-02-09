import time
import tensorflow as tf
from typing import Callable, Any, Dict

from src import commons
from src.traffic_sign_classifier import ops
from src.traffic_sign_classifier.params import params
from src.traffic_sign_classifier.model import LeNet, dataset_pipeline
from src.traffic_sign_classifier.preprocess import preprocess


def test(
        dataset_: Callable,
        model_builder: Callable,
        params: Dict
):
    optimizer_ = tf.keras.optimizers.Adam(0.1)
    checkpoints = ops.CheckpointCallback(model_dir=params["model_dir"], optimizer=optimizer_, model=model_builder)
    checkpoints.restore()
    dataset_iterator = iter(dataset_)
    
    all_labels = []
    all_preds = []
    for pp in range(0, 30):
        print('Running Batch = ', pp)
        feature, target = next(dataset_iterator)
        pred_logits = model_builder(feature)
        pred_prob = tf.nn.softmax(pred_logits)

        labels = tf.argmax(target, axis=-1).numpy()
        preds = tf.argmax(pred_prob, axis=-1).numpy()
        all_labels += list(labels)
        all_preds += list(preds)
    
    assert(len(all_labels) == len(all_preds))
    match = sum([1 for i, j in zip(all_labels, all_preds) if i == j])
    print("Accuracy: ", match/len(all_preds))
    
    
if __name__ == "__main__":
    test_data_path = "./data/test.p"
    test_data = commons.read_pickle(test_data_path)
    params["batch_size"] = 421
    test_features = test_data["features"]
    test_labels = test_data["labels"]
    print(f"[Train]: features={test_features.shape}, labels={test_labels.shape}")

    test_preprocess = preprocess(mode="eval")
    test_dataset_ = dataset_pipeline(test_features, test_labels, test_preprocess, params, mode="test")
    model_fn_ = LeNet(num_classes=43)
    test(test_dataset_, model_fn_, params)
